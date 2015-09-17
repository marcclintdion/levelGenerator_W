//------------------------------------------------------

if(spikyBall_00_3_position[0] <= -2.5)///wall_Collision
{
        spikyBall_00_3_Velocity[0] *= -1;
}
if(spikyBall_00_3_position[0] >= 2.5)////wall_Collision
{
        spikyBall_00_3_Velocity[0] *= -1;
}                                                        

//------------------------------------------------------

if(spikyBall_00_3_position[1] < .35)///wall_Collision
{
        spikyBall_00_3_Velocity[1] *= -1;
}

//------------------------------------------------------

if(spikyBall_00_3_position[2] <= -2.5)///wall_Collision
{
        spikyBall_00_3_Velocity[2] *= -1;
}
if(spikyBall_00_3_position[2] >= 2.5)////wall_Collision
{
        spikyBall_00_3_Velocity[2] *= -1;
}                                                   

//------------------------------------------------------

                      ///___3_1___//
spikyBall_00_3_1_vector[0] = spikyBall_00_1_position[0] - spikyBall_00_3_position[0];
spikyBall_00_3_1_vector[1] = spikyBall_00_1_position[1] - spikyBall_00_3_position[1];
spikyBall_00_3_1_vector[2] = spikyBall_00_1_position[2] - spikyBall_00_3_position[2];
distance_3_1          = sqrt(((spikyBall_00_3_1_vector[0])*(spikyBall_00_3_1_vector[0]))
                                                     + ((spikyBall_00_3_1_vector[1])*(spikyBall_00_3_1_vector[1]))
                                                     + ((spikyBall_00_3_1_vector[2])*(spikyBall_00_3_1_vector[2])));
                                                     ///___3_1___//

                      ///___3_2___//
spikyBall_00_3_2_vector[0] = spikyBall_00_2_position[0] - spikyBall_00_3_position[0];
spikyBall_00_3_2_vector[1] = spikyBall_00_2_position[1] - spikyBall_00_3_position[1];
spikyBall_00_3_2_vector[2] = spikyBall_00_2_position[2] - spikyBall_00_3_position[2];
distance_3_2          = sqrt(((spikyBall_00_3_2_vector[0])*(spikyBall_00_3_2_vector[0]))
                                                     + ((spikyBall_00_3_2_vector[1])*(spikyBall_00_3_2_vector[1]))
                                                     + ((spikyBall_00_3_2_vector[2])*(spikyBall_00_3_2_vector[2])));
                                                     ///___3_2___//

//////////////////___3_1___////////////////////////////////////////////////      
if(distance_3_1 <= radius_3+radius_1 && !collision_3_1)
 {                                     
     SWIZZLE_Velocity_3_1[0]   = spikyBall_00_1_Velocity[0];
     SWIZZLE_Velocity_3_1[1]   = spikyBall_00_1_Velocity[1];
     SWIZZLE_Velocity_3_1[2]   = spikyBall_00_1_Velocity[2];//__radial_Collision

     spikyBall_00_1_Velocity[0] = spikyBall_00_3_Velocity[0];                              
     spikyBall_00_1_Velocity[1] = spikyBall_00_3_Velocity[1];                              
     spikyBall_00_1_Velocity[2] = spikyBall_00_3_Velocity[2];

     spikyBall_00_3_Velocity[0] = SWIZZLE_Velocity_3_1[0];
     spikyBall_00_3_Velocity[1] = SWIZZLE_Velocity_3_1[1];
     spikyBall_00_3_Velocity[2] = SWIZZLE_Velocity_3_1[2];                  

     collision_3_1 = true;                               
}                                     

if(distance_3_1 > radius_3+radius_1 && collision_3_1)
{
      collision_3_1 = false; 
} 
//////////////////___3_1___////////////////////////////////////////////////     

//////////////////___3_2___////////////////////////////////////////////////      
if(distance_3_2 <= radius_3+radius_2 && !collision_3_2)
 {                                     
     SWIZZLE_Velocity_3_2[0]   = spikyBall_00_2_Velocity[0];
     SWIZZLE_Velocity_3_2[1]   = spikyBall_00_2_Velocity[1];
     SWIZZLE_Velocity_3_2[2]   = spikyBall_00_2_Velocity[2];//__radial_Collision

     spikyBall_00_2_Velocity[0] = spikyBall_00_3_Velocity[0];                              
     spikyBall_00_2_Velocity[1] = spikyBall_00_3_Velocity[1];                              
     spikyBall_00_2_Velocity[2] = spikyBall_00_3_Velocity[2];

     spikyBall_00_3_Velocity[0] = SWIZZLE_Velocity_3_2[0];
     spikyBall_00_3_Velocity[1] = SWIZZLE_Velocity_3_2[1];
     spikyBall_00_3_Velocity[2] = SWIZZLE_Velocity_3_2[2];                  

     collision_3_2 = true;                               
}                                     

if(distance_3_2 > radius_3+radius_2 && collision_3_2)
{
      collision_3_2 = false; 
} 
//////////////////___3_2___////////////////////////////////////////////////     

 //***************************************************************   
//__3__//                                                //__3__// 
         spikyBall_00_3_position[0] += spikyBall_00_3_Velocity[0];
         spikyBall_00_3_position[1] += spikyBall_00_3_Velocity[1];
         spikyBall_00_3_position[2] += spikyBall_00_3_Velocity[2];    
//__3__//                                                //__3__//    
//***************************************************************  
              glTranslatef(spikyBall_00_3_position[0],spikyBall_00_3_position[1],spikyBall_00_3_position[2]);
              spinX_Ball_3 =  spikyBall_00_3_Velocity[2];//+.000000001 <----Used to prevent scaling @ zeroVelocity
              spinZ_Ball_3 = -spikyBall_00_3_Velocity[0]-.000000001;

              if(spikyBall_00_3_Velocity[0] == 0 && spikyBall_00_3_Velocity[1] == 0 && spikyBall_00_3_Velocity[2] == 0)
              {
                   spinBall_3 = 0;
              }
             
              
              spikyBall_00_3_Velocity[1]  -= 0.002 + spikyBall_00_3_Velocity[1]*spikyBall_00_3_Velocity[1];          
             
              
              velocitySwap_3[0] = spikyBall_00_3_Velocity[0];
              velocitySwap_3[2] = spikyBall_00_3_Velocity[2];              
              
              if(velocitySwap_3[0] < 0.0)
              {
                   velocitySwap_3[0] *= -1.0;
              }              
              if(velocitySwap_3[2] < 0.0)
              {
                   velocitySwap_3[2] *= -1.0;
              }               
              
              velocityIncreaseRotation_3 = (velocitySwap_3[0] + velocitySwap_3[2])*100;
              
              spinBall_3 += velocityIncreaseRotation_3;
              
              glRotatef(spinBall_3, spinX_Ball_3, 0.0, spinZ_Ball_3);

                                                                   

              //glInterleavedArrays( GL_T2F_N3F_V3F, 0, spikyBall_00);
              //glDrawArrays( GL_TRIANGLES, 0, 432);
