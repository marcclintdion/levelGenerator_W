float depth = 0.05;

float texsize = 512;

varying vec2 texCoord;
varying vec3 vertex_pos;
varying vec3 light_pos;
varying float vertex_dist;
varying float light_dist;
varying float dist_val;

uniform sampler2D stepmap;
uniform sampler2D texmap;

void intersect_square_cone_3step (inout vec3 dp, in vec3 ds);

void main(void)
{
   vec4 t,c;
   vec3 l,s;
   vec3 pt_eye, pt_light;
   float a;

   // ray intersect in view direction
   a  = -depth / vertex_pos.z;
   s = vertex_pos * a;
   s.z = 1.0;
  
   //	find the distance to the actualy heightfield
   pt_eye = vec3 (texCoord, 0.0);
   intersect_square_cone_3step (pt_eye, s);
  
   /*
   gl_FragColor = vec4(pt_eye.z, 0, 0, 0);
   return;//*/
  
   // get rm and color texture points
   c=texture2D(texmap,pt_eye.xy);

   // expand normal from normal map in local polygon space
   // blue = df/dx
   // alpha = df/dy (image coords are no longer backward!)
   // note: I _need_ the texture size to scale the normal properly!
   t=texture2D(stepmap, pt_eye.xy);
   t = vec4 ((t.ba-0.5) * (-depth * texsize), 1.0, 0.0);
   t=normalize(t);

   // adjust the hit-position
   // (only useful if the light is near relative
   // to the depth)
   //p -= v*d*a;
   
   // compute attenuation
   float att = gl_LightSource[0].linearAttenuation;
   att = min (1.0, 1.0 / (light_dist*att));
   
   // rescale the light vector
   l = att * normalize(light_pos);

   // compute the final color
   gl_FragColor = vec4(
   			gl_LightSource[0].ambient.xyz*c.xyz
   			+gl_LightSource[0].diffuse.xyz*c.xyz*max(0.0,dot(l,t.xyz)), 
   			1.0);
}

// experimental (distance is taken into account)
void intersect_square_cone_3step (inout vec3 dp, in vec3 ds)
{
   // the "not Z" component of the direction vector (for a square cone)
   float iz = max(abs(ds.x),abs(ds.y));
   // SOR
   const float w = 1.2;
   // my starting location (is at z=0)
   // texture lookup
   vec4 t;

   //  initial step is farther out (a *HACK*)
   dp += 0.3 * ds;

   //	find the initial location and height
   t=texture2D(stepmap,dp.xy);
   // right, I need to take one step.
   // I use the current height above the texture,
   // and the information about the cone-ratio
   // to size a single step.  So it is fast and 
   // precise!  (like a coneified version of
   // "space leaping", but adapted from voxels)
   dp += ds * w * (t.r - dp.z) / (iz/(t.g*t.g) + 1.0);
   
   // and repeat a few (4x) times 
   //*
   t=texture2D(stepmap,dp.xy);
   dp += ds * w * (t.r - dp.z) / (iz/(t.g*t.g) + 1.0);
   t=texture2D(stepmap,dp.xy);
   dp += ds * w * (t.r - dp.z) / (iz/(t.g*t.g) + 1.0);
      
   // all done
   return;
}
