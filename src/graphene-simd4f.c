/* graphene-simd4f.c
 *
 * Copyright © 2014  Emmanuele Bassi
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

/**
 * SECTION:graphene-simd4f
 * @Title: SIMD vector
 * @short_description: Low level floating point 4-sized vector
 *
 * The #graphene_simd4f_t type wraps a platform specific implementation of
 * a vector of four floating point values.
 *
 * Graphene can be compiled to use different implementations of the SIMD
 * types, and will generally prefer the faster hardware-backed implementation
 * if one is available.
 *
 * The #graphene_simd4f_t should be treated as an opaque, integral type;
 * you cannot access its components directly, and you can only operate on
 * all components at the same time.
 */

#include "config.h"

#include <string.h>
#include <math.h>

#include "graphene-simd4f.h"

/**
 * graphene_simd4f_t:
 *
 * A vector type containing four floating point values.
 *
 * Since: 1.0
 */

/* fast paths are all defined in the graphene-simd4f.h header */
#if defined(GRAPHENE_USE_SSE) || defined(GRAPHENE_USE_GCC) || defined(GRAPHENE_USE_ARM_NEON)

/**
 * graphene_simd4f_init:
 * @x: the first component of the vector
 * @y: the second component of the vector
 * @z: the third component of the vector
 * @w: the fourth component of the vector
 *
 * Initializes a #graphene_simd4f_t with the given values.
 *
 * Returns: the initialized #graphene_simd4f_t
 *
 * Since: 1.0
 */
graphene_simd4f_t
(graphene_simd4f_init) (float x,
                        float y,
                        float z,
                        float w)
{
  return graphene_simd4f_init (x, y, z, w);
}

/**
 * graphene_simd4f_init_zero:
 *
 * Initializes a #graphene_simd4f_t with 0 in all components.
 *
 * Returns: the initialized #graphene_simd4f_t
 *
 * Since: 1.0
 */
graphene_simd4f_t
(graphene_simd4f_init_zero) (void)
{
  return graphene_simd4f_init_zero ();
}

/**
 * graphene_simd4f_init_4f:
 * @v: (array fixed-size=4): an array of at least 4 floating
 *   point values
 *
 * Initializes a #graphene_simd4f_t using an array of 4 floating
 * point values.
 *
 * Returns: the initialized #graphene_simd4f_t
 *
 * Since: 1.0
 */
graphene_simd4f_t
(graphene_simd4f_init_4f) (const float *v)
{
  return graphene_simd4f_init_4f (v);
}

/**
 * graphene_simd4f_init_3f:
 * @v: (array fixed-size=3): an array of at least 3 floating
 *   point values
 *
 * Initializes a #graphene_simd4f_t using an array of 3 floating
 * point values.
 *
 * Returns: the initialized #graphene_simd4f_t
 *
 * Since: 1.0
 */
graphene_simd4f_t
(graphene_simd4f_init_3f) (const float *v)
{
  return graphene_simd4f_init_3f (v);
}

/**
 * graphene_simd4f_init_2f:
 * @v: (array fixed-size=2): an array of at least 2 floating
 * point values
 *
 * Initializes a #graphene_simd4f_t using an array of 2 floating
 * point values.
 *
 * Returns: the initialized #graphene_simd4f_t
 *
 * Since: 1.0
 */
graphene_simd4f_t
(graphene_simd4f_init_2f) (const float *v)
{
  return graphene_simd4f_init_2f (v);
}

/**
 * graphene_simd4f_dup_4f:
 * @s: a #graphene_simd4f_t
 * @v: (out) (array fixed-size=4): return location for an
 *   array of at least 4 floating point values
 *
 * Copies the contents of a #graphene_simd4f_t into an
 * array of floating points.
 *
 * Since: 1.0
 */
void
(graphene_simd4f_dup_4f) (const graphene_simd4f_t  s,
                          float                   *v)
{
  graphene_simd4f_dup_4f (s, v);
}

/**
 * graphene_simd4f_dup_3f:
 * @s: a #graphene_simd4f_t
 * @v: (out) (array fixed-size=3): return location for an
 *   array of at least 3 floating point values
 *
 * Copies the contents of a #graphene_simd4f_t into an
 * array of floating points.
 *
 * Since: 1.0
 */
void
(graphene_simd4f_dup_3f) (const graphene_simd4f_t  s,
                          float                   *v)
{
  graphene_simd4f_dup_3f (s, v);
}

/**
 * graphene_simd4f_dup_2f:
 * @s: a #graphene_simd4f_t
 * @v: (out) (array fixed-size=2): return location for an
 *   array of at least 2 floating point values
 *
 * Copies the contents of a #graphene_simd4f_t into an
 * array of floating points.
 *
 * Since: 1.0
 */
void
(graphene_simd4f_dup_2f) (const graphene_simd4f_t  s,
                          float                   *v)
{
  graphene_simd4f_dup_2f (s, v);
}

/**
 * graphene_simd4f_get_x:
 * @s: a #graphene_simd4f_t
 *
 * Retrieves the first component of @s.
 *
 * Returns: the first component of a #graphene_simd4f_t
 *
 * Since: 1.0
 */
float
(graphene_simd4f_get_x) (const graphene_simd4f_t s)
{
  return graphene_simd4f_get_x (s);
}

/**
 * graphene_simd4f_get_y:
 * @s: a #graphene_simd4f_t
 *
 * Retrieves the second component of @s.
 *
 * Returns: the second component of a #graphene_simd4f_t
 *
 * Since: 1.0
 */
float
(graphene_simd4f_get_y) (const graphene_simd4f_t s)
{
  return graphene_simd4f_get_y (s);
}

/**
 * graphene_simd4f_get_z:
 * @s: a #graphene_simd4f_t
 *
 * Retrieves the third component of @s.
 *
 * Returns: the third component of a #graphene_simd4f_t
 *
 * Since: 1.0
 */
float
(graphene_simd4f_get_z) (const graphene_simd4f_t s)
{
  return graphene_simd4f_get_z (s);
}

/**
 * graphene_simd4f_get_w:
 * @s: a #graphene_simd4f_t
 *
 * Retrieves the fourth component of @s.
 *
 * Returns: the fourth component of a #graphene_simd4f_t
 *
 * Since: 1.0
 */
float
(graphene_simd4f_get_w) (const graphene_simd4f_t s)
{
  return graphene_simd4f_get_w (s);
}

/**
 * graphene_simd4f_splat:
 * @v: a floating point value
 *
 * Sets all the components of a new #graphene_simd4f_t to the
 * same value @v.
 *
 * Returns: the initialized #graphene_simd4f_t
 *
 * Since: 1.0
 */
graphene_simd4f_t
(graphene_simd4f_splat) (float v)
{
  return graphene_simd4f_splat (v);
}

/**
 * graphene_simd4f_splat_x:
 * @s: a #graphene_simd4f_t
 *
 * Sets all the components of a new #graphene_simd4f_t to the
 * same value of the first component of the passed vector.
 *
 * Returns: the initialized #graphene_simd4f_t
 *
 * Since: 1.0
 */
graphene_simd4f_t
(graphene_simd4f_splat_x) (const graphene_simd4f_t s)
{
  return graphene_simd4f_splat_x (s);
}

/**
 * graphene_simd4f_splat_y:
 * @s: a #graphene_simd4f_t
 *
 * Sets all the components of a new #graphene_simd4f_t to the
 * same value of the second component of the passed vector.
 *
 * Returns: the initialized #graphene_simd4f_t
 *
 * Since: 1.0
 */
graphene_simd4f_t
(graphene_simd4f_splat_y) (const graphene_simd4f_t s)
{
  return graphene_simd4f_splat_y (s);
}

/**
 * graphene_simd4f_splat_z:
 * @s: a #graphene_simd4f_t
 *
 * Sets all the components of a #graphene_simd4f_t to the
 * same value of the third component of the passed vector.
 *
 * Returns: the initialized #graphene_simd4f_t
 *
 * Since: 1.0
 */
graphene_simd4f_t
(graphene_simd4f_splat_z) (const graphene_simd4f_t s)
{
  return graphene_simd4f_splat_z (s);
}

/**
 * graphene_simd4f_splat_w:
 * @s: a #graphene_simd4f_t
 *
 * Sets all the components of a #graphene_simd4f_t to the
 * same value of the fourth component of the passed vector.
 *
 * Returns: the initialized #graphene_simd4f_t
 *
 * Since: 1.0
 */
graphene_simd4f_t
(graphene_simd4f_splat_w) (const graphene_simd4f_t s)
{
  return graphene_simd4f_splat_w (s);
}

/**
 * graphene_simd4f_reciprocal:
 * @s: a #graphene_simd4f_t
 *
 * Computes the reciprocal of every component of @s.
 *
 * Returns: a vector containing the reciprocal of the
 *   passed vector
 *
 * Since: 1.0
 */
graphene_simd4f_t
(graphene_simd4f_reciprocal) (const graphene_simd4f_t s)
{
  return graphene_simd4f_reciprocal (s);
}

/**
 * graphene_simd4f_sqrt:
 * @s: a #graphene_simd4f_t
 *
 * Computes the square root of every component of @s.
 *
 * |[<!-- language="C" -->
 *   {
 *     .x = sqrt (s.x),
 *     .y = sqrt (s.y),
 *     .z = sqrt (s.z),
 *     .w = sqrt (s.w)
 *   }
 * ]|
 *
 * Returns: a vector containing the square root of the
 *   passed vector
 *
 * Since: 1.0
 */
graphene_simd4f_t
(graphene_simd4f_sqrt) (const graphene_simd4f_t s)
{
  return graphene_simd4f_sqrt (s);
}

/**
 * graphene_simd4f_rsqrt:
 * @s: a #graphene_simd4f_t
 *
 * Computes the reciprocal square root of every component
 * of @s.
 *
 * |[<!-- language="C" -->
 *   {
 *     .x = 1.0 / sqrt (s.x),
 *     .y = 1.0 / sqrt (s.y),
 *     .z = 1.0 / sqrt (s.z),
 *     .w = 1.0 / sqrt (s.w)
 *   }
 * ]|
 *
 * Returns: a vector containing the reciprocal square root
 *   of the passed vector
 *
 * Since: 1.0
 */
graphene_simd4f_t
(graphene_simd4f_rsqrt) (const graphene_simd4f_t s)
{
  return graphene_simd4f_rsqrt (s);
}

/**
 * graphene_simd4f_add:
 * @a: a #graphene_simd4f_t
 * @b: a #graphene_simd4f_t
 *
 * Creates a new #graphene_simd4f_t vector where each
 * component is the sum of the respective components
 * in @a and @b.
 *
 * |[<!-- lanugage="C" -->
 *   {
 *     .x = a.x + b.x,
 *     .y = a.y + b.y,
 *     .z = a.z + b.z,
 *     .w = a.w + b.w
 *   }
 * ]|
 *
 * Returns: the sum vector
 *
 * Since: 1.0
 */
graphene_simd4f_t
(graphene_simd4f_add) (const graphene_simd4f_t a,
                       const graphene_simd4f_t b)
{
  return graphene_simd4f_add (a, b);
}

/**
 * graphene_simd4f_sub:
 * @a: a #graphene_simd4f_t
 * @b: a #graphene_simd4f_t
 *
 * Creates a new #graphene_simd4f_t vector where each
 * component is the subtraction of the respective components
 * in @a and @b.
 *
 * |[<!-- lanugage="C" -->
 *   {
 *     .x = a.x - b.x,
 *     .y = a.y - b.y,
 *     .z = a.z - b.z,
 *     .w = a.w - b.w
 *   }
 * ]|
 *
 * Returns: the subtraction vector
 *
 * Since: 1.0
 */
graphene_simd4f_t
(graphene_simd4f_sub) (const graphene_simd4f_t a,
                       const graphene_simd4f_t b)
{
  return graphene_simd4f_sub (a, b);
}

/**
 * graphene_simd4f_mul:
 * @a: a #graphene_simd4f_t
 * @b: a #graphene_simd4f_t
 *
 * Creates a new #graphene_simd4f_t vector where each
 * component is the multiplication of the respective components
 * in @a and @b.
 *
 * |[<!-- lanugage="C" -->
 *   {
 *     .x = a.x * b.x,
 *     .y = a.y * b.y,
 *     .z = a.z * b.z,
 *     .w = a.w * b.w
 *   }
 * ]|
 *
 * Returns: the multiplication vector
 *
 * Since: 1.0
 */
graphene_simd4f_t
(graphene_simd4f_mul) (const graphene_simd4f_t a,
                       const graphene_simd4f_t b)
{
  return graphene_simd4f_mul (a, b);
}

/**
 * graphene_simd4f_div:
 * @a: a #graphene_simd4f_t
 * @b: a #graphene_simd4f_t
 *
 * Creates a new #graphene_simd4f_t vector where each
 * component is the division of the respective components
 * in @a and @b.
 *
 * |[<!-- lanugage="C" -->
 *   {
 *     .x = a.x / b.x,
 *     .y = a.y / b.y,
 *     .z = a.z / b.z,
 *     .w = a.w / b.w
 *   }
 * ]|
 *
 * Returns: the division vector
 *
 * Since: 1.0
 */
graphene_simd4f_t
(graphene_simd4f_div) (const graphene_simd4f_t a,
                       const graphene_simd4f_t b)
{
  return graphene_simd4f_div (a, b);
}

/**
 * graphene_simd4f_cross3:
 * @a: a #graphene_simd4f_t
 * @b: a #graphene_simd4f_t
 *
 * Creates a new #graphene_simd4f_t vector where each
 * component contains the 3-way cross product of the
 * given @a and @b vectors. You can access the result
 * as a floating point value through graphene_simd4f_get_x().
 *
 * Returns: the cross3 vector
 *
 * Since: 1.0
 */
graphene_simd4f_t
(graphene_simd4f_cross3) (const graphene_simd4f_t a,
                          const graphene_simd4f_t b)
{
  return graphene_simd4f_cross3 (a, b);
}

/**
 * graphene_simd4f_min:
 * @a: a #graphene_simd4f_t
 * @b: a #graphene_simd4f_t
 *
 * Creates a new #graphene_simd4f_t that contains the
 * minimum value of each component of @a and @b.
 *
 * Returns: the new minimum vector
 *
 * Since: 1.0
 */
graphene_simd4f_t
(graphene_simd4f_min) (const graphene_simd4f_t a,
                       const graphene_simd4f_t b)
{
  return graphene_simd4f_min (a, b);
}

/**
 * graphene_simd4f_max:
 * @a: a #graphene_simd4f_t
 * @b: a #graphene_simd4f_t
 *
 * Creates a new #graphene_simd4f_t that contains the
 * maximum value of each component of @a and @b.
 *
 * Returns: the new maximum vector
 *
 * Since: 1.0
 */
graphene_simd4f_t
(graphene_simd4f_max) (const graphene_simd4f_t a,
                       const graphene_simd4f_t b)
{
  return graphene_simd4f_max (a, b);
}

graphene_simd4f_t
(graphene_simd4f_shuffle_wxyz) (const graphene_simd4f_t s)
{
  return graphene_simd4f_shuffle_wxyz (s);
}

graphene_simd4f_t
(graphene_simd4f_shuffle_zwxy) (const graphene_simd4f_t s)
{
  return graphene_simd4f_shuffle_zwxy (s);
}

graphene_simd4f_t
(graphene_simd4f_shuffle_yzwx) (const graphene_simd4f_t s)
{
  return graphene_simd4f_shuffle_yzwx (s);
}

graphene_simd4f_t
(graphene_simd4f_zero_w) (const graphene_simd4f_t s)
{
  return graphene_simd4f_zero_w (s);
}

graphene_simd4f_t
(graphene_simd4f_zero_zw) (const graphene_simd4f_t s)
{
  return graphene_simd4f_zero_zw (s);
}

graphene_simd4f_t
(graphene_simd4f_merge_high) (const graphene_simd4f_t a,
                              const graphene_simd4f_t b)
{
  return graphene_simd4f_merge_high (a, b);
}

graphene_simd4f_t
(graphene_simd4f_flip_sign_0101) (const graphene_simd4f_t s)
{
  return graphene_simd4f_flip_sign_0101 (s);
}

graphene_simd4f_t
(graphene_simd4f_flip_sign_1010) (const graphene_simd4f_t s)
{
  return graphene_simd4f_flip_sign_1010 (s);
}

gboolean
(graphene_simd4f_cmp_eq) (const graphene_simd4f_t a,
                          const graphene_simd4f_t b)
{
  return graphene_simd4f_cmp_eq (a, b);
}

gboolean
(graphene_simd4f_cmp_neq) (const graphene_simd4f_t a,
                           const graphene_simd4f_t b)
{
  return graphene_simd4f_cmp_neq (a, b);
}

#else /* GRAPHENE_USE_SCALAR */

graphene_simd4f_t
(graphene_simd4f_init) (float x,
                        float y,
                        float z,
                        float w)
{
  graphene_simd4f_t s = { x, y, z, w };
  return s;
}

graphene_simd4f_t
(graphene_simd4f_init_zero) (void)
{
  return graphene_simd4f_init (0.f, 0.f, 0.f, 0.f);
}

graphene_simd4f_t
(graphene_simd4f_init_4f) (const float *v)
{
  return graphene_simd4f_init (v[0], v[1], v[2], v[3]);
}

graphene_simd4f_t
(graphene_simd4f_init_3f) (const float *v)
{
  return graphene_simd4f_init (v[0], v[1], v[2], 0.f);
}

graphene_simd4f_t
(graphene_simd4f_init_2f) (const float *v)
{
  return graphene_simd4f_init (v[0], v[1], 0.f, 0.f);
}

void
(graphene_simd4f_dup_4f) (const graphene_simd4f_t  s,
                          float                   *v)
{
  memcpy (v, &s, sizeof (float) * 4);
}

void
(graphene_simd4f_dup_3f) (const graphene_simd4f_t  s,
                          float                   *v)
{
  memcpy (v, &s, sizeof (float) * 3);
}

void
(graphene_simd4f_dup_2f) (const graphene_simd4f_t  s,
                        float                   *v)
{
  memcpy (v, &s, sizeof (float) * 2);
}

float
(graphene_simd4f_get_x) (const graphene_simd4f_t s)
{
  return s.x;
}

float
(graphene_simd4f_get_y) (const graphene_simd4f_t s)
{
  return s.y;
}

float
(graphene_simd4f_get_z) (const graphene_simd4f_t s)
{
  return s.z;
}

float
(graphene_simd4f_get_w) (const graphene_simd4f_t s)
{
  return s.w;
}

graphene_simd4f_t
(graphene_simd4f_splat) (float v)
{
  graphene_simd4f_t s = { v, v, v, v };
  return s;
}

graphene_simd4f_t
(graphene_simd4f_splat_x) (graphene_simd4f_t v)
{
  graphene_simd4f_t s = { v.x, v.x, v.x, v.x };
  return s;
}

graphene_simd4f_t
(graphene_simd4f_splat_y) (graphene_simd4f_t v)
{
  graphene_simd4f_t s = { v.y, v.y, v.y, v.y };
  return s;
}

graphene_simd4f_t
(graphene_simd4f_splat_z) (graphene_simd4f_t v)
{
  graphene_simd4f_t s = { v.z, v.z, v.z, v.z };
  return s;
}

graphene_simd4f_t
(graphene_simd4f_splat_w) (graphene_simd4f_t v)
{
  graphene_simd4f_t s = { v.w, v.w, v.w, v.w };
  return s;
}

graphene_simd4f_t
(graphene_simd4f_reciprocal) (graphene_simd4f_t v)
{
  graphene_simd4f_t s = {
    1.0f / v.x,
    1.0f / v.y,
    1.0f / v.z,
    1.0f / v.w
  };
  return s;
}

graphene_simd4f_t
(graphene_simd4f_sqrt) (graphene_simd4f_t v)
{
  graphene_simd4f_t s = {
    sqrt (v.x),
    sqrt (v.y),
    sqrt (v.z),
    sqrt (v.w)
  };
  return s;
}

graphene_simd4f_t
(graphene_simd4f_rsqrt) (graphene_simd4f_t v)
{
  graphene_simd4f_t s = {
    1.0f / sqrt (v.x),
    1.0f / sqrt (v.y),
    1.0f / sqrt (v.z),
    1.0f / sqrt (v.w)
  };
  return s;
}

graphene_simd4f_t
(graphene_simd4f_add) (const graphene_simd4f_t a,
                       const graphene_simd4f_t b)
{
  graphene_simd4f_t s = {
    a.x + b.x,
    a.y + b.y,
    a.z + b.z,
    a.w + b.w
  };
  return s;
}

graphene_simd4f_t
(graphene_simd4f_sub) (const graphene_simd4f_t a,
                       const graphene_simd4f_t b)
{
  graphene_simd4f_t s = {
    a.x - b.x,
    a.y - b.y,
    a.z - b.z,
    a.w - b.w
  };
  return s;
}

graphene_simd4f_t
(graphene_simd4f_mul) (const graphene_simd4f_t a,
                       const graphene_simd4f_t b)
{
  graphene_simd4f_t s = {
    a.x * b.x,
    a.y * b.y,
    a.z * b.z,
    a.w * b.w
  };
  return s;
}

graphene_simd4f_t
(graphene_simd4f_div) (const graphene_simd4f_t a,
                       const graphene_simd4f_t b)
{
  graphene_simd4f_t s = {
    a.x / b.x,
    a.y / b.y,
    a.z / b.z,
    a.w / b.w
  };
  return s;
}

graphene_simd4f_t
(graphene_simd4f_cross3) (const graphene_simd4f_t a,
                          const graphene_simd4f_t b)
{
  return graphene_simd4f_init (a.y * b.z - a.z * b.y,
                               a.z * b.x - a.x * b.z,
                               a.x * b.y - a.y * b.x,
                               0.f);
}

graphene_simd4f_t
(graphene_simd4f_min) (const graphene_simd4f_t a,
                       const graphene_simd4f_t b)
{
  return graphene_simd4f_init (a.x < b.x ? a.x : b.x,
                               a.y < b.y ? a.y : b.y,
                               a.z < b.z ? a.z : b.z,
                               a.w < b.w ? a.w : b.w);
}

graphene_simd4f_t
(graphene_simd4f_max) (const graphene_simd4f_t a,
                       const graphene_simd4f_t b)
{
  return graphene_simd4f_init (a.x > b.x ? a.x : b.x,
                               a.y > b.y ? a.y : b.y,
                               a.z > b.z ? a.z : b.z,
                               a.w > b.w ? a.w : b.w);
}

graphene_simd4f_t
(graphene_simd4f_shuffle_wxyz) (const graphene_simd4f_t s)
{
  return graphene_simd4f_init (s.w, s.x, s.y, s.z);
}

graphene_simd4f_t
(graphene_simd4f_shuffle_zwxy) (const graphene_simd4f_t s)
{
  return graphene_simd4f_init (s.z, s.w, s.x, s.y);
}

graphene_simd4f_t
(graphene_simd4f_shuffle_yzwx) (const graphene_simd4f_t s)
{
  return graphene_simd4f_init (s.y, s.z, s.w, s.x);
}

graphene_simd4f_t
(graphene_simd4f_zero_w) (const graphene_simd4f_t s)
{
  return graphene_simd4f_init (s.x, s.y, s.z, 0.0f); 
}

graphene_simd4f_t
(graphene_simd4f_zero_zw) (const graphene_simd4f_t s)
{
  return graphene_simd4f_init (s.x, s.y, 0.0f, 0.0f);
}

graphene_simd4f_t
(graphene_simd4f_merge_high) (const graphene_simd4f_t a,
                              const graphene_simd4f_t b)
{
  return graphene_simd4f_init (a.z, a.w, b.z, b.w);
}

graphene_simd4f_t
(graphene_simd4f_flip_sign_0101) (const graphene_simd4f_t s)
{
  return graphene_simd4f_init (s.x, -s.y, s.z, -s.w);
}

graphene_simd4f_t
(graphene_simd4f_flip_sign_1010) (const graphene_simd4f_t s)
{
  return graphene_simd4f_init (-s.x, s.y, -s.z, s.w);
}

gboolean
(graphene_simd4f_cmp_eq) (const graphene_simd4f_t a,
                          const graphene_simd4f_t b)
{
  return a.x == b.x &&
         a.y == b.y &&
         a.z == b.z &&
         a.w == b.w;
}

gboolean
(graphene_simd4f_cmp_neq) (const graphene_simd4f_t a,
                           const graphene_simd4f_t b)
{
  return a.x != b.x &&
         a.y != b.y &&
         a.z != b.z &&
         a.w != b.w;
}

#endif /* GRAPHENE_USE_SCALAR */