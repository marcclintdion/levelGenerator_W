//------------------------------------------------------
if(spikyBall_0_POSITION[0] <= -5)///wall_Collision
{
        spikyBall_00_1_Velocity[0] *= -1;
}
if(spikyBall_0_POSITION[0] >= 5)////wall_Collision
{
        spikyBall_00_1_Velocity[0] *= -1;
}                                                        
//------------------------------------------------------
if(spikyBall_0_POSITION[1] < .35)///wall_Collision
{
        spikyBall_00_1_Velocity[1] *= -1.0;
}
//------------------------------------------------------
if(spikyBall_0_POSITION[2] <= -5.0)///wall_Collision
{
        spikyBall_00_1_Velocity[2] *= -1;
}
if(spikyBall_0_POSITION[2] >= 5)////wall_Collision
{
        spikyBall_00_1_Velocity[2] *= -1;
}                                                   
//------------------------------------------------------
//***************************************************************   
//__1__//                                                //__1__// 
         spikyBall_0_POSITION[0] += spikyBall_00_1_Velocity[0];
         spikyBall_0_POSITION[1] += spikyBall_00_1_Velocity[1]*2;
         spikyBall_0_POSITION[2] += spikyBall_00_1_Velocity[2];    
//__1__//                                                //__1__//    
//***************************************************************  
              
              spikyBall_0_ROTATE[0] =  spikyBall_00_1_Velocity[2];//+.000000001 <----Used to prevent scaling @ zeroVelocity
              spikyBall_0_ROTATE[2] = -spikyBall_00_1_Velocity[0]-.000000001;

              if(spikyBall_00_1_Velocity[0] == 0 && spikyBall_00_1_Velocity[1] == 0 && spikyBall_00_1_Velocity[2] == 0)
              {
                   spinBall_1 = 0.0;
              }
              spikyBall_00_1_Velocity[1]  -= 0.001 + spikyBall_00_1_Velocity[1] * spikyBall_00_1_Velocity[1];
              
              velocitySwap_1[0] = spikyBall_00_1_Velocity[0];
              velocitySwap_1[2] = spikyBall_00_1_Velocity[2];              
              
              if(velocitySwap_1[0] < 0.0)
              {
                   velocitySwap_1[0] *= -1.0;
              }              
              if(velocitySwap_1[2] < 0.0)
              {
                   velocitySwap_1[2] *= -1.0;
              }               
              
              velocityIncreaseRotation_1 = (velocitySwap_1[0] + velocitySwap_1[2])*100;

              spikyBall_0_ROTATE[3] += velocityIncreaseRotation_1;
              


                                                                  





