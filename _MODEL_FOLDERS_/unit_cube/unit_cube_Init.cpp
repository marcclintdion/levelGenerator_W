        //------------------------------------------------------------------------------------------                                                       
        #ifdef __APPLE__                                                                                                                                   
        //---------------                                                                                                                                  
        filePathName = [[NSBundle mainBundle] pathForResource:@"unit_cube_DOT3" ofType:@"png"];                                           
        if(filePathName != nil)                                                                                                                                
        {                                                                                                                                                  
                image = imgLoadImage([filePathName cStringUsingEncoding:NSASCIIStringEncoding]);                                                           
                glGenTextures(1, &unit_cube_NORMALMAP);                                                                                       
                glBindTexture(GL_TEXTURE_2D, unit_cube_NORMALMAP);                                                                            
                ConfigureAndLoadTexture(image->data,  image->width, image->height );                                                                       
                imgDestroyImage(image);                                                                                                                    
        }else                                                                                                                                              
            {                                                                                                                                              
               //add error file output here                                                                                                                
            }  
        filePathName = nil;  
        //---------------------                                                                                                                            
        filePathName = [[NSBundle mainBundle] pathForResource:@"unit_cube" ofType:@"png"];                                                
        if(filePathName != nil)                                                                                                                                
        {                                                                                                                                                  
                image = imgLoadImage([filePathName cStringUsingEncoding:NSASCIIStringEncoding]);                                                           
                glGenTextures(1, &unit_cube_TEXTUREMAP);                                                                                      
                glBindTexture(GL_TEXTURE_2D, unit_cube_TEXTUREMAP);                                                                           
                ConfigureAndLoadTexture(image->data,  image->width, image->height );                                                                       
                imgDestroyImage(image);                                                                                                                    
                                                                                                                                          
        }else                                                                                                                                              
            {                                                                                                                                              
               //add error file output here                                                                                                                
            }  
        filePathName = nil;                                                                                                                                              
        //---------------                                                                                                                                  
        #endif                                                                                                                                             
        //------------------------------------------------------------------------------------------                                                       
        #ifdef WIN32                                                                                                                                       
        loadTexture("_MODEL_FOLDERS_/unit_cube/unit_cube_DOT3.png",          unit_cube_NORMALMAP);                
        loadTexture("_MODEL_FOLDERS_/unit_cube/unit_cube.png",               unit_cube_TEXTUREMAP);               
        #endif                                                                                                                                             
        //------------------------------------------------------------------------------------------------------------//___LOAD_VBO                        
        #include    "unit_cube.cpp"                                                                                                         
        glGenBuffers(1,              &unit_cube_VBO);                                                                                         
        glBindBuffer(GL_ARRAY_BUFFER, unit_cube_VBO);                                                                                         
        glBufferData(GL_ARRAY_BUFFER, sizeof(unit_cube), unit_cube, GL_STATIC_DRAW);                                             
        glBindBuffer(GL_ARRAY_BUFFER, 0);                                                                                                                  
        //------------------------------------------------------------------------------------------------------------                                     
        #include    "unit_cube_INDICES.cpp"                                                                                                 
        glGenBuffers(1,              &unit_cube_INDICES_VBO);                                                                                   
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, unit_cube_INDICES_VBO);                                                                           
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unit_cube_INDICES), unit_cube_INDICES, GL_STATIC_DRAW);                       
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);                                                                                                            
        //------------------------------------------------------------------------------------------------------------                                       
        //====================================================================================   
        model_01_collisionInfo[0] = -1;
        model_01_collisionInfo[1] = 1;
        model_01_collisionInfo[2] = -1;
        model_01_collisionInfo[3] = 1;
        model_01_collisionInfo[4] = -1;
        model_01_collisionInfo[5] = 1;
        model_01_collisionInfo[6] = boxCount;        
        //-----------------------------------
        collisionBoxArray[boxCount][0] = -1;
        collisionBoxArray[boxCount][1] = 1;
        collisionBoxArray[boxCount][2] = -1;
        collisionBoxArray[boxCount][3] = 1;
        collisionBoxArray[boxCount][4] = -1;
        collisionBoxArray[boxCount][5] = 1;
        collisionBoxArray[boxCount][6] = boxCount;
        boxCount++;
