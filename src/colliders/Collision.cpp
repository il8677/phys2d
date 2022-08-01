#include "Collision.h"

#include <phys2d/maths/mat2.h>
#include <phys2d/Body.h>

#include <functional>
#include <float.h>
#include <tuple>

namespace phys2d{

    void circleCircle(Contact& contact);
    void circlePoly(Contact& contact);
    void polyPoly(Contact& contact);

    void dispatchContact(Contact& contact){
        static std::function<void(Contact&)> resolves[2][2] = {
            {circleCircle, circlePoly},
            {circlePoly, polyPoly}}; // 2d array with function pointers corresponding to the Enum pairs of two contact bodies

        Body* A = contact.A;
        Body* B = contact.B;

        resolves[A->shape->type][B->shape->type](contact);
    }

    void circleCircle(Contact& contact){
        Body* bA = contact.A;
        Body* bB = contact.B;

        ShapeCircle* A = (ShapeCircle*)bA->shape;
        ShapeCircle* B = (ShapeCircle*)bB->shape;

        Vec2 colNormal = bB->position - bA->position;
        float dist = colNormal.magnitude();
        float totalRadius = A->radius + B->radius;

        if(dist > totalRadius){
            contact.contactCount = 0;
            return;
        }

        contact.contactCount = 1;
        contact.pen = totalRadius - dist;
        contact.normal = colNormal.normalized();
        contact.contactPoints[0] = contact.normal * A->radius + bA->position;
    }

    void circlePoly(Contact& contact){
        Body* bA;
        Body* bB;

        bool doFlip;

        // Make A the cirlce body and B the polygon
        if(contact.A->shape->type == Shape::Type::CIRCLE){
            bA = contact.A;
            bB = contact.B;

            doFlip = false;
        }else{
            bA = contact.B;
            bB = contact.A;

            doFlip = true;
        }

        ShapeCircle* A = (ShapeCircle*)bA->shape;
        ShapePoly* B = (ShapePoly*)bB->shape;

        Mat2 aOrient(bA->rotation); // Rotation matricies of both objects
        Mat2 bOrient(bB->rotation);

        Vec2 circleCenter = bA->position;

        circleCenter = bOrient.transposed() * (circleCenter - bB->position); // Transform circle into B space

        float bestPen = -FLT_MAX; // Find the vertex with the maxiumum penetration into the circle
        size_t bestIndex = 0;

        for(int i = 0; i < B->points.size(); i++){
            float p = B->normals[i].dot(circleCenter - B->points[i]);

            if(p > A->radius) return;

            if(p > bestPen){
                bestPen = p;
                bestIndex = i;
            }
        }
        if(bestPen < 0.1e-10f){ // Only one collision point (Collision on a vertex)
            contact.contactCount = 1;
            contact.normal = -(bOrient * B->normals[bestIndex]);
            contact.contactPoints[0] = contact.normal * A->radius + bA->position;
            contact.pen = A->radius;
            return;
        }

        // Get the face of the collision
        Vec2 bFace[2];
        bFace[0] = B->points[bestIndex];
        size_t next = bestIndex + 1;
        if(next == B->points.size()) next = 0;
        bFace[1] = B->points[next];

        // Calculate penetration across each direction of the face
        float d1 = (circleCenter-bFace[0]).dot(bFace[1] - bFace[0]);
        float d2 = (circleCenter-bFace[1]).dot(bFace[0] - bFace[1]);
        contact.pen = A->radius - bestPen;

        if(d1 <= 0.0f){ // Collision on vertex 1
            float dist = (circleCenter - bFace[0]).dot(circleCenter - bFace[0]); // Distance between circle and colliding vertex

            if(dist > A->radius * A->radius) return;

            contact.contactCount = 1;

            Vec2 n = bFace[0] - circleCenter; // Colision normal
            n = bOrient * n;
            n.normalize();
            contact.normal = n;

            bFace[0] = bOrient * bFace[0] + bB->position; // Transform into world space
            contact.contactPoints[0] = bFace[0];

        }else if (d2 <= 0.0f){ // Collision on vertex 2
            float dist = (circleCenter - bFace[1]).dot(circleCenter - bFace[1]);

            if(dist > A->radius * A->radius) return;

            contact.contactCount = 1;

            Vec2 n = bFace[1] - circleCenter;
            n = bOrient * n;
            n.normalize();
            contact.normal = n;

            bFace[1] = bOrient * bFace[1] + bB->position;
            contact.contactPoints[0] = bFace[1];

        }else{ // Collision on face
            Vec2 n = B->normals[bestIndex];
            if((circleCenter-bFace[0]).dot(n) > A->radius) return;

            n = bOrient * n; // Transform normal line
            contact.normal = -n;
            contact.contactPoints[0] = contact.normal * A->radius + bA->position;
            contact.contactCount = 1;
        }

        if(doFlip) contact.normal = -contact.normal; // Flip if circle-polygon was flipped
    }

    // Returns the index of the face, and the amount it penetrates
    std::tuple<size_t, float> getMaxPen(Body* bA, Body* bB){
        float bestPen = -FLT_MAX;
        size_t bestIndex;

        ShapePoly* A = (ShapePoly*)bA->shape;
        ShapePoly* B = (ShapePoly*)bB->shape;

        for(size_t i = 0; i < A->points.size(); i++){
            Vec2 an = A->normals[i];
            Mat2 ar = Mat2(bA->rotation);
            Vec2 ran = ar * an; // Rotated normal vertex

            // Space transformation
            Mat2 brT = Mat2(bB->rotation).transposed();
            an = brT * ran; // Normal vector in B space

            Vec2 bmax = B->getMaxPoint(-an); // Closest B vertex to the normal vector

            // Space transformation
            Vec2 ap = A->points[i];
            ap = ar * ap + bA->position;
            ap -= bB->position;
            ap = brT * ap;

            // Penetration of vertex with the closest point
            float bmodelpen = an.dot(bmax-ap);

            if(bmodelpen > bestPen){
                bestPen = bmodelpen;
                bestIndex = i;
            }
        }

        return std::make_tuple(bestIndex, bestPen);
    }

    int clip(Vec2 n, float c, Vec2* face){
        int sp = 0;
        Vec2 out[2];
        out[0] = face[0];
        out[1] = face[1];

        float d1 = n.dot(face[0]) - c;
        float d2 = n.dot(face[1]) - c;

        // Negative clip
        if(d1 <= 0.0f) out[sp++] = face[0];
        if(d2 <= 0.0f) out[sp++] = face[1];

        if(d1 * d2 < 0.0f){
            float a = d1 / (d1-d2);
            out[sp] = face[0] + a * (face[1] - face[0]);
            sp++;
        }

        face[0] = out[0];
        face[1] = out[1];

        return sp;
    }

    void polyPoly(Contact& contact){
        Body* bA = contact.A;
        Body* bB = contact.B;

        if(bA->getType() == Body::BodyType::STATIC && bB->getType() == Body::BodyType::STATIC) return;

        ShapePoly* A = (ShapePoly*)bA->shape;
        ShapePoly* B = (ShapePoly*)bB->shape;

        // Find penetration of both objects
        auto [indexa, pena] = getMaxPen(bA, bB);
        auto [indexb, penb] = getMaxPen(bB, bA);

        if(pena >= 0) return; // No collision
        if(penb >= 0) return;

        size_t refFaceIndex;
        bool isB;

        // Find which face is the reference face
        ShapePoly* ref;
        ShapePoly* inc;
        Body* bRef;
        Body* bInc;

        if(pena >= pena * 0.01f + penb * 0.95f){ // a is ref face
            ref = A;
            bRef = bA;
            inc = B;
            bInc = bB;

            refFaceIndex = indexa;

            isB = false;
        }else{ // b is ref face
            ref = B;
            bRef = bB;
            inc = A;
            bInc = bA;

            refFaceIndex = indexb;

            isB = true;
        }

        // Set up the incident face
        Mat2 refOrient(bRef->rotation); // Rotation matricies of both objects
        Mat2 incOrient(bInc->rotation);

        Vec2 refNorm = refOrient * ref->normals[refFaceIndex]; // Orient the ref face to incident face space
        refNorm = incOrient.transposed() * refNorm;

        // find the reference face most away from the normal
        size_t incFaceIndex = 0;
        float minDot = FLT_MAX;

        for(size_t i = 0; i < inc->points.size(); i++){
            float dot = refNorm.dot(inc->normals[i]);
            if(dot < minDot){
                minDot = dot;
                incFaceIndex = i;
            }
        }

        // Get the word verticies of the bodies
        Vec2 incidentFaceWorld[2];
        incidentFaceWorld[0] = incOrient * inc->points[incFaceIndex] + bInc->position;
        if(++incFaceIndex >= inc->points.size()) incFaceIndex = 0;
        incidentFaceWorld[1] = incOrient * inc->points[incFaceIndex] + bInc->position;

        Vec2 referenceFaceWorld[2];
        referenceFaceWorld[0] = refOrient * ref->points[refFaceIndex] + bRef->position;
        if(++refFaceIndex >= ref->points.size()) refFaceIndex = 0;
        referenceFaceWorld[1] = refOrient * ref->points[refFaceIndex] + bRef->position;

        Vec2 refFace = referenceFaceWorld[1] - referenceFaceWorld[0];
        refFace.normalize();
        
        Vec2 refFaceNormal = refFace.getNormal();

        // Calculating the clipping planes of the bodies
        float c = refFaceNormal.dot(referenceFaceWorld[0]);
        float n = -refFace.dot(referenceFaceWorld[0]);
        float p =  refFace.dot(referenceFaceWorld[1]);

        if(clip(-refFace, n, incidentFaceWorld) < 2) return; // error
        if(clip(refFace, p, incidentFaceWorld) < 2) return; // error

        contact.normal = isB? -refFaceNormal : refFaceNormal;

        int contactCount = 0;
        float sep = refFaceNormal.dot(incidentFaceWorld[0]) - c;

        if(sep <= 0.0f){
            contact.contactPoints[contactCount++] = incidentFaceWorld[0];
            contact.pen = -sep;
        }else{
            contact.pen = 0;
        }

        sep = refFaceNormal.dot(incidentFaceWorld[1]) - c;

        if(sep <= 0.0f){
            contact.contactPoints[contactCount++] = incidentFaceWorld[1];
            contact.pen += -sep;

            contact.pen /= (float)contactCount;
        }

        contact.contactCount = contactCount;
    }
}
