//------------------------------------------------------

if(spikyBall_00_2_position[0] <= -2.5)///wall_Collision
{
        spikyBall_00_2_Velocity[0] *= -1;
}
if(spikyBall_00_2_position[0] >= 2.5)////wall_Collision
{
        spikyBall_00_2_Velocity[0] *= -1;
}                                                        

//------------------------------------------------------

if(spikyBall_00_2_position[1] < .35)///wall_Collision
{
        spikyBall_00_2_Velocity[1] *= -1;
}

//------------------------------------------------------

if(spikyBall_00_2_position[2] <= -2.5)///wall_Collision
{
        spikyBall_00_2_Velocity[2] *= -1;
}
if(spikyBall_00_2_position[2] >= 2.5)////wall_Collision
{
        spikyBall_00_2_Velocity[2] *= -1;
}                                                   

//------------------------------------------------------
                      ///___2_1___//
spikyBall_00_2_1_vector[0] = spikyBall_00_1_position[0] - spikyBall_00_2_position[0];
spikyBall_00_2_1_vector[1] = spikyBall_00_1_position[1] - spikyBall_00_2_position[1];
spikyBall_00_2_1_vector[2] = spikyBall_00_1_position[2] - spikyBall_00_2_position[2];
distance_2_1          = sqrt(((spikyBall_00_2_1_vector[0])*(spikyBall_00_2_1_vector[0]))
                                                     + ((spikyBall_00_2_1_vector[1])*(spikyBall_00_2_1_vector[1]))
                                                     + ((spikyBall_00_2_1_vector[2])*(spikyBall_00_2_1_vector[2])));
                                                     ///___2_1___//

//////////////////___2_1___////////////////////////////////////////////////      
if(distance_2_1 <= radius_2+radius_1 && !collision_2_1)
 {                                     
     SWIZZLE_Velocity_2_1[0]   = spikyBall_00_1_Velocity[0];
     SWIZZLE_Velocity_2_1[1]   = spikyBall_00_1_Velocity[1];
     SWIZZLE_Velocity_2_1[2]   = spikyBall_00_1_Velocity[2];//__radial_Collision

     spikyBall_00_1_Velocity[0] = spikyBall_00_2_Velocity[0];                              
     spikyBall_00_1_Velocity[1] = spikyBall_00_2_Velocity[1];                              
     spikyBall_00_1_Velocity[2] = spikyBall_00_2_Velocity[2];

     spikyBall_00_2_Velocity[0] = SWIZZLE_Velocity_2_1[0];
     spikyBall_00_2_Velocity[1] = SWIZZLE_Velocity_2_1[1];
     spikyBall_00_2_Velocity[2] = SWIZZLE_Velocity_2_1[2];                  

     collision_2_1 = true;                               
}                                     

if(distance_2_1 > radius_2+radius_1 && collision_2_1)
{
      collision_2_1 = false; 
} 
//////////////////___2_1___////////////////////////////////////////////////     

 //***************************************************************   
//__2__//                                                //__2__// 
         spikyBall_00_2_position[0] += spikyBall_00_2_Velocity[0];
         spikyBall_00_2_position[1] += spikyBall_00_2_Velocity[1];
         spikyBall_00_2_position[2] += spikyBall_00_2_Velocity[2];    
//__2__//                                                //__2__//    
//***************************************************************  
              glTranslatef(spikyBall_00_2_position[0],spikyBall_00_2_position[1],spikyBall_00_2_position[2]);
              spinX_Ball_2 =  spikyBall_00_2_Velocity[2];//+.000000001 <----Used to prevent scaling @ zeroVelocity
              spinZ_Ball_2 = -spikyBall_00_2_Velocity[0]-.000000001;

              if(spikyBall_00_2_Velocity[0] == 0 && spikyBall_00_2_Velocity[1] == 0 && spikyBall_00_2_Velocity[2] == 0)
              {
                    spinBall_2 = 0;
              }

              spikyBall_00_2_Velocity[1]  -= 0.0006 + spikyBall_00_2_Velocity[1]*spikyBall_00_2_Velocity[1];

              velocitySwap_2[0] = spikyBall_00_2_Velocity[0];
              velocitySwap_2[2] = spikyBall_00_2_Velocity[2];              
              
              if(velocitySwap_2[0] < 0.0)
              {
                   velocitySwap_2[0] *= -1.0;
              }              
              if(velocitySwap_2[2] < 0.0)
              {
                   velocitySwap_2[2] *= -1.0;
              }               
              
              velocityIncreaseRotation_2 = (velocitySwap_2[0] + velocitySwap_2[2])*100;             
             
              spinBall_2 += velocityIncreaseRotation_2;
              
              glRotatef(spinBall_2, spinX_Ball_2, 0.0, spinZ_Ball_2);

                                                               

              //glInterleavedArrays( GL_T2F_N3F_V3F, 0, spikyBall_00);
              //glDrawArrays( GL_TRIANGLES, 0, 432);
