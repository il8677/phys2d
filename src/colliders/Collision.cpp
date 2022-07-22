#include "Collision.h"

#include <phys2d/maths/mat2.h>
#include <phys2d/Body.h>

#include <functional>
#include <float.h>
#include <tuple>

#include <iostream>

namespace phys2d{
    void dispatchContact(Contact& contact){
        static std::function<void(Contact&)> resolves[2][2] = {
            {circleCircle, circlePoly},
            {circlePoly, polyPoly}};

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

        if(contact.A->shape->type == Shape::Type::CIRCLE){
            bA = contact.A;
            bA = contact.B;
        }else{
            bA = contact.B;
            bB = contact.A;
        }

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
            Vec2 ran = ar * an;

            // Space transformation
            Mat2 brT = Mat2(bB->rotation).transposed();
            an = brT * ran;

            Vec2 bmax = B->getMaxPoint(-an);

            // Space transformation
            Vec2 ap = A->points[i];
            ap = ar * ap + bA->position;
            ap -= bB->position;
            ap = brT * ap;

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

        ShapePoly* A = (ShapePoly*)bA->shape;
        ShapePoly* B = (ShapePoly*)bB->shape;

        auto [indexa, pena] = getMaxPen(bA, bB);
        auto [indexb, penb] = getMaxPen(bB, bA);

        if(pena >= 0) return; // No collision
        if(penb >= 0) return;

        size_t refFaceIndex;
        bool isB;

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

        // Find the incident face
        Mat2 refOrient(bRef->rotation);
        Mat2 incOrient(bInc->rotation);

        Vec2 refNorm = refOrient * ref->normals[refFaceIndex];
        refNorm = incOrient.transposed() * refNorm;

        // find the face most away from the normal
        size_t incFaceIndex = 0;
        float minDot = FLT_MAX;

        for(size_t i = 0; i < inc->points.size(); i++){
            float dot = refNorm.dot(inc->normals[i]);
            if(dot < minDot){
                minDot = dot;
                incFaceIndex = i;
            }
        }

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

//================================================================
//================================================================
//================================================================
//================================================================
//================================================================

int32_t Clip( Vec2 n, float c, Vec2 *face )
{
  uint32_t sp = 0;
  Vec2 out[2] = {
    face[0],
    face[1]
  };

  // Retrieve distances from each endpoint to the line
  // d = ax + by - c
  float d1 = n.dot( face[0] ) - c;
  float d2 = n.dot( face[1] ) - c;

  // If negative (behind plane) clip
  if(d1 <= 0.0f) out[sp++] = face[0];
  if(d2 <= 0.0f) out[sp++] = face[1];
  
  // If the points are on different sides of the plane
  if(d1 * d2 < 0.0f) // less than to ignore -0.0f
  {
    // Push interesection point
    float alpha = d1 / (d1 - d2);
    out[sp] = face[0] + alpha * (face[1] - face[0]);
    ++sp;
  }

  // Assign our new converted values
  face[0] = out[0];
  face[1] = out[1];

  assert( sp != 3 );

  return sp;
}

void PolygontoPolygon(Contact& c)
{
 Body* a = c.A;
 Body* b = c.B;

  ShapePoly *A = reinterpret_cast<ShapePoly *>(a->shape);
  ShapePoly *B = reinterpret_cast<ShapePoly *>(b->shape);
  c.contactCount = 0;

  // Check for a separating axis with A's face planes
  auto [faceA, penetrationA] = getMaxPen(a, b );
  if(penetrationA >= 0.0f)
    return;

  // Check for a separating axis with B's face planes
  auto [faceB, penetrationB] = getMaxPen(a, b );
  if(penetrationB >= 0.0f)
    return;

  uint32_t referenceIndex;
  bool flip; // Always point from a to b

  ShapePoly *RefPoly; // Reference
  ShapePoly *IncPoly; // Incident
    Body* bRef;
    Body* bInc;

  // Determine which shape contains reference face
  if(penetrationA >= penetrationA * 0.01f + penetrationB * 0.95f)
  {
    RefPoly = A;
    bRef = a;
    IncPoly = B;
    bInc = b;
    referenceIndex = faceA;
    flip = false;
  }
  else
  {
    RefPoly = B;
    bRef = b;
    IncPoly = A;
    bInc = a;
    referenceIndex = faceB;
    flip = true;
  }
    Mat2 refOrient(bRef->rotation);
    Mat2 incOrient(bInc->rotation);

  // World space incident face
  Vec2 incidentFace[2];
  Vec2 referenceNormal = RefPoly->normals[referenceIndex];

  // Calculate normal in incident's frame of reference
  referenceNormal = refOrient * referenceNormal; // To world space
  referenceNormal = incOrient.transposed() * referenceNormal; // To incident's model space

  // Find most anti-normal face on incident polygon
  int32_t incidentFaceI = 0;
  float minDot = FLT_MAX;
  for(uint32_t i = 0; i < IncPoly->points.size(); ++i)
  {
    float dot = referenceNormal.dot(IncPoly->normals[i]);
    if(dot < minDot)
    {
      minDot = dot;
      incidentFaceI = i;
    }
  }

  // Assign face vertices for incidentFace
  incidentFace[0] = incOrient * IncPoly->points[incidentFaceI] + bInc->position;
  incidentFaceI = incidentFaceI + 1 >= (uint32_t)IncPoly->points.size() ? 0 : incidentFaceI + 1;
  incidentFace[1] = incOrient * IncPoly->points[incidentFaceI] + bInc->position;
  //        y
  //        ^  ->n       ^
  //      +---c ------posPlane--
  //  x < | i |\
  //      +---+ c-----negPlane--
  //             \       v
  //              r
  //
  //  r : reference face
  //  i : incident poly
  //  c : clipped point
  //  n : incident normal

  // Setup reference face vertices
  Vec2 v1 = RefPoly->points[referenceIndex];
  referenceIndex = referenceIndex + 1 == RefPoly->points.size() ? 0 : referenceIndex + 1;
  Vec2 v2 = RefPoly->points[referenceIndex];

  // Transform vertices to world space
  v1 = refOrient * v1 + bRef->position;
  v2 = refOrient * v2 + bRef->position;

  // Calculate reference face side normal in world space
  Vec2 sidePlaneNormal = (v2 - v1);
  sidePlaneNormal.normalize();

  // Orthogonalize
  Vec2 refFaceNormal( sidePlaneNormal.y, -sidePlaneNormal.x );

  // ax + by = c
  // c is distance from origin
  float refC = refFaceNormal.dot(v1);
  float negSide = -sidePlaneNormal.dot( v1 );
  float posSide =  sidePlaneNormal.dot( v2 );

  // Clip incident face to reference face side planes
  if(Clip( -sidePlaneNormal, negSide, incidentFace ) < 2)
    return; // Due to floating point error, possible to not have required points

  if(Clip(  sidePlaneNormal, posSide, incidentFace ) < 2)
    return; // Due to floating point error, possible to not have required points

  // Flip
  c.normal = flip ? -refFaceNormal : refFaceNormal;

  // Keep points behind reference face
  uint32_t cp = 0; // clipped points behind reference face
  float separation = refFaceNormal.dot(incidentFace[0] ) - refC;
  if(separation <= 0.0f)
  {
    c.contactPoints[cp] = incidentFace[0];
    c.pen = -separation;
    ++cp;
  }
  else
    c.pen = 0;

  separation = refFaceNormal.dot( incidentFace[1] ) - refC;
  if(separation <= 0.0f)
  {
    c.contactPoints[cp] = incidentFace[1];

    c.pen += -separation;
    ++cp;

    // Average penetration
    c.pen /= (float)cp;
  }

  c.contactCount = cp;
}


}