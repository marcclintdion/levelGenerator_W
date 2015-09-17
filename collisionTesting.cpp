//CollisionCheck_DOWN(collisionBoxArray[1][0]-0.5, collisionBoxArray[1][0]+0.5, collisionBoxArray[1][0]-0.5, collisionBoxArray[1][0]+0.5);       
        backGroundModel_POSITION[1][0] += backGroundModel_VELOCITY[1][0];
        backGroundModel_POSITION[1][1] += backGroundModel_VELOCITY[1][1];       
       
       
        //####################################################################################################################        
        for(int i = 1; i < boxCount; i++)
        {
            collisionBoxArray[i][0] += backGroundModel_VELOCITY[i][0];
            collisionBoxArray[i][1] += backGroundModel_VELOCITY[i][0];        
            collisionBoxArray[i][2] += backGroundModel_VELOCITY[i][1];        
            collisionBoxArray[i][3] += backGroundModel_VELOCITY[i][1];        
        
        
                                    if(collisionBoxArray[i][0] < -11.0 || collisionBoxArray[i][1] > 11.0)
                                    {
                                            backGroundModel_VELOCITY[i][0] *= -1.0;
                                    }
                                    if(collisionBoxArray[i][2] < -7.5 || collisionBoxArray[i][3] > 7.5)
                                    {
                                            backGroundModel_VELOCITY[i][1] *= -1.0;
                                    }        
        
        }
        
        
        
        
        
        
        
        
        
        
        
       
        
        
        
        
