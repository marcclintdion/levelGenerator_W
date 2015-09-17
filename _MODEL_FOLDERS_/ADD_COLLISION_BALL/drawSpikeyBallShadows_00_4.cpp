glPushMatrix();       
     glColor4f(spikyBall_00_4_position[1] * scaleFlyingSpikeyBallHeightFade * scaleFlyingSpikeyBallHeightFade, spikyBall_00_4_position[1] * scaleFlyingSpikeyBallHeightFade * scaleFlyingSpikeyBallHeightFade, spikyBall_00_4_position[1] * scaleFlyingSpikeyBallHeightFade * scaleFlyingSpikeyBallHeightFade, 1.0);
     //-----------------------------------------------------------------------------------------------------------------------------------------------------------
     glTranslatef(moveSet[0], -moveSet[2], 0.0f);
     glTranslatef(flyingSpikyBallShadowPosition_00_4[0]+spikyBall_00_4_position[0], flyingSpikyBallShadowPosition_00_4[1]-spikyBall_00_4_position[2], flyingSpikyBallShadowPosition_00_4[2]);
     glScalef(1.0+spikyBall_00_4_position[1]*scaleFlyingSpikyBallShadow_00_4*scaleFlyingSpikyBallShadow_00_4, 1.0+spikyBall_00_4_position[1]*scaleFlyingSpikyBallShadow_00_4*scaleFlyingSpikyBallShadow_00_4, 1.0+spikyBall_00_4_position[1]*scaleFlyingSpikyBallShadow_00_4*scaleFlyingSpikyBallShadow_00_4);
     glRotatef(spinBall_4, spinX_Ball_4, 0, spinZ_Ball_4);         
     //-----------------------------------------------------------------------------------------------------------------------------------------------------------
     #include "_MODEL_FOLDERS_/spikyBalls/drawSpikeyBallShadowsModel.cpp"
     //-----------------------------------------------------------------------------------------------------------------------------------------------------------
     glColor4f(spikyBall_00_4_position[1] * scaleFlyingSpikeyBallHeightFade * scaleFlyingSpikeyBallHeightFade+.3, spikyBall_00_4_position[1] * scaleFlyingSpikeyBallHeightFade * scaleFlyingSpikeyBallHeightFade+.3, spikyBall_00_4_position[1] * scaleFlyingSpikeyBallHeightFade * scaleFlyingSpikeyBallHeightFade+.3, 1.0);
glPopMatrix();
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                          //-----------------------------
                                                  glLoadIdentity();
                                          //-----------------------------
///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
