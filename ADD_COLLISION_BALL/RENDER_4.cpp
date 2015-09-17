//------------------------------------------------------

if(spikyBall_00_4_position[0] <= -2.50)///leftWall_Collision
{
        spikyBall_00_4_Velocity[0] *= -1;
}
if(spikyBall_00_4_position[0] >= 2.50)////rightWall_Collision
{
        spikyBall_00_4_Velocity[0] *= -1;
}                                                        

//------------------------------------------------------

if(spikyBall_00_4_position[1] < .35)///floor_Collision
{
        spikyBall_00_4_Velocity[1] *= -1;
}

//------------------------------------------------------

if(spikyBall_00_4_position[2] <= -2.50)///farWall_Collision
{
        spikyBall_00_4_Velocity[2] *= -1;
}
if(spikyBall_00_4_position[2] >= 2.50)////nearWall_Collision
{
        spikyBall_00_4_Velocity[2] *= -1;
}                                                   

//------------------------------------------------------
                      ///___4_1___//
spikyBall_00_4_1_vector[0] = spikyBall_00_1_position[0] - spikyBall_00_4_position[0];
spikyBall_00_4_1_vector[1] = spikyBall_00_1_position[1] - spikyBall_00_4_position[1];
spikyBall_00_4_1_vector[2] = spikyBall_00_1_position[2] - spikyBall_00_4_position[2];
distance_4_1          = sqrt(((spikyBall_00_4_1_vector[0])*(spikyBall_00_4_1_vector[0]))
                                                     + ((spikyBall_00_4_1_vector[1])*(spikyBall_00_4_1_vector[1]))
                                                     + ((spikyBall_00_4_1_vector[2])*(spikyBall_00_4_1_vector[2])));
                                                     ///___4_1___//

                      ///___4_2___//
spikyBall_00_4_2_vector[0] = spikyBall_00_2_position[0] - spikyBall_00_4_position[0];
spikyBall_00_4_2_vector[1] = spikyBall_00_2_position[1] - spikyBall_00_4_position[1];
spikyBall_00_4_2_vector[2] = spikyBall_00_2_position[2] - spikyBall_00_4_position[2];
distance_4_2          = sqrt(((spikyBall_00_4_2_vector[0])*(spikyBall_00_4_2_vector[0]))
                                                     + ((spikyBall_00_4_2_vector[1])*(spikyBall_00_4_2_vector[1]))
                                                     + ((spikyBall_00_4_2_vector[2])*(spikyBall_00_4_2_vector[2])));
                                                     ///___4_2___//

                      ///___4_3___//
spikyBall_00_4_3_vector[0] = spikyBall_00_3_position[0] - spikyBall_00_4_position[0];
spikyBall_00_4_3_vector[1] = spikyBall_00_3_position[1] - spikyBall_00_4_position[1];
spikyBall_00_4_3_vector[2] = spikyBall_00_3_position[2] - spikyBall_00_4_position[2];
distance_4_3          = sqrt(((spikyBall_00_4_3_vector[0])*(spikyBall_00_4_3_vector[0]))
                                                     + ((spikyBall_00_4_3_vector[1])*(spikyBall_00_4_3_vector[1]))
                                                     + ((spikyBall_00_4_3_vector[2])*(spikyBall_00_4_3_vector[2])));
                                                     ///___4_3___//

//////////////////___4_1___////////////////////////////////////////////////      
if(distance_4_1 <= radius_4+radius_1 && !collision_4_1)
 {                                     
     SWIZZLE_Velocity_4_1[0]   = spikyBall_00_1_Velocity[0];
     SWIZZLE_Velocity_4_1[1]   = spikyBall_00_1_Velocity[1];
     SWIZZLE_Velocity_4_1[2]   = spikyBall_00_1_Velocity[2];//__radial_Collision

     spikyBall_00_1_Velocity[0] = spikyBall_00_4_Velocity[0];                              
     spikyBall_00_1_Velocity[1] = spikyBall_00_4_Velocity[1];                              
     spikyBall_00_1_Velocity[2] = spikyBall_00_4_Velocity[2];

     spikyBall_00_4_Velocity[0] = SWIZZLE_Velocity_4_1[0];
     spikyBall_00_4_Velocity[1] = SWIZZLE_Velocity_4_1[1];
     spikyBall_00_4_Velocity[2] = SWIZZLE_Velocity_4_1[2];                  

     collision_4_1 = true;                               
}                                     

if(distance_4_1 > radius_4+radius_1 && collision_4_1)
{
      collision_4_1 = false; 
} 
//////////////////___4_1___////////////////////////////////////////////////     

//////////////////___4_2___////////////////////////////////////////////////      
if(distance_4_2 <= radius_4+radius_2 && !collision_4_2)
 {                                     
     SWIZZLE_Velocity_4_2[0]   = spikyBall_00_2_Velocity[0];
     SWIZZLE_Velocity_4_2[1]   = spikyBall_00_2_Velocity[1];
     SWIZZLE_Velocity_4_2[2]   = spikyBall_00_2_Velocity[2];//__radial_Collision

     spikyBall_00_2_Velocity[0] = spikyBall_00_4_Velocity[0];                              
     spikyBall_00_2_Velocity[1] = spikyBall_00_4_Velocity[1];                              
     spikyBall_00_2_Velocity[2] = spikyBall_00_4_Velocity[2];

     spikyBall_00_4_Velocity[0] = SWIZZLE_Velocity_4_2[0];
     spikyBall_00_4_Velocity[1] = SWIZZLE_Velocity_4_2[1];
     spikyBall_00_4_Velocity[2] = SWIZZLE_Velocity_4_2[2];                  

     collision_4_2 = true;                               
}                                     

if(distance_4_2 > radius_4+radius_2 && collision_4_2)
{
      collision_4_2 = false; 
} 
//////////////////___4_2___////////////////////////////////////////////////     

//////////////////___4_3___////////////////////////////////////////////////      
if(distance_4_3 <= radius_4+radius_3 && !collision_4_3)
 {                                     
     SWIZZLE_Velocity_4_3[0]   = spikyBall_00_3_Velocity[0];
     SWIZZLE_Velocity_4_3[1]   = spikyBall_00_3_Velocity[1];
     SWIZZLE_Velocity_4_3[2]   = spikyBall_00_3_Velocity[2];//__radial_Collision

     spikyBall_00_3_Velocity[0] = spikyBall_00_4_Velocity[0];                              
     spikyBall_00_3_Velocity[1] = spikyBall_00_4_Velocity[1];                              
     spikyBall_00_3_Velocity[2] = spikyBall_00_4_Velocity[2];

     spikyBall_00_4_Velocity[0] = SWIZZLE_Velocity_4_3[0];
     spikyBall_00_4_Velocity[1] = SWIZZLE_Velocity_4_3[1];
     spikyBall_00_4_Velocity[2] = SWIZZLE_Velocity_4_3[2];                  

     collision_4_3 = true;                               
}                                     

if(distance_4_3 > radius_4+radius_3 && collision_4_3)
{
      collision_4_3 = false; 
} 
//////////////////___4_3___////////////////////////////////////////////////     

 //***************************************************************   
//__4__//                                                //__4__// 
         spikyBall_00_4_position[0] += spikyBall_00_4_Velocity[0];
         spikyBall_00_4_position[1] += spikyBall_00_4_Velocity[1];
         spikyBall_00_4_position[2] += spikyBall_00_4_Velocity[2];    
//__4__//                                                //__4__//    
//***************************************************************  
              glTranslatef(spikyBall_00_4_position[0],spikyBall_00_4_position[1],spikyBall_00_4_position[2]);
              spinBall_4 += 1;                                                                  
              spinX_Ball_4 =  spikyBall_00_4_Velocity[2];//+.000000001 <----Used to prevent scaling @ zeroVelocity
              spinZ_Ball_4 = -spikyBall_00_4_Velocity[0]-.000000001;

              if(spikyBall_00_4_Velocity[0] == 0 && spikyBall_00_4_Velocity[1] == 0 && spikyBall_00_4_Velocity[2] == 0)
              {
                     spinBall_4 = 0;
              }


              spikyBall_00_4_Velocity[1]  -= 0.00105 + spikyBall_00_4_Velocity[1]*spikyBall_00_4_Velocity[1];//_RANDOM_GRAVITY 


              velocitySwap_4[0] = spikyBall_00_4_Velocity[0];                           
              velocitySwap_4[2] = spikyBall_00_4_Velocity[2];                           


              if(velocitySwap_4[0] < 0.0)                                               
              {                                                                         
                     velocitySwap_4[0] *= -1.0;                                           
              }                                                                         
              if(velocitySwap_4[2] < 0.0)                                               
              {                                                                         
                     velocitySwap_4[2] *= -1.0;                                           
              }                                                                         

              velocityIncreaseRotation_4 = (velocitySwap_4[0] + velocitySwap_4[2])*100; 

              spinBall_4 += velocityIncreaseRotation_4;                                 

              glRotatef(spinBall_4*spinVelocity_4, spinX_Ball_4, 0, spinZ_Ball_4);

            //  glPushMatrix();
            //         glLoadIdentity(); 
            //         glRotatef(-spinBall_4*spinVelocity_4, -spinX_Ball_4, 0, spinZ_Ball_4); 
            //         glLightfv (GL_LIGHT0,GL_POSITION, lightPos_spikyBall_00_4);
            //         glLightf (GL_LIGHT0, GL_QUADRATIC_ATTENUATION, lightAttenuation_spikyBall_00_4);       
            //  glPopMatrix();                                                                    

