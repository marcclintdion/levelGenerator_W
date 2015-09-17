        //------------------------------------------------------------------------------------------                                                       
        #ifdef __APPLE__                                                                                                                                   
        //---------------                                                                                                                                  
        filePathName = [[NSBundle mainBundle] pathForResource:@"unit_cube_DOT3" ofType:@"bmp"];                                           
        if(fileName != nil)                                                                                                                                
        {                                                                                                                                                  
                image = imgLoadImage([filePathName cStringUsingEncoding:NSASCIIStringEncoding]);                                                           
                glGenTextures(1, &unit_cube_NORMALMAP);                                                                                       
                glBindTexture(GL_TEXTURE_2D, unit_cube_NORMALMAP);                                                                            
                ConfigureAndLoadTexture(image->data,  image->width, image->height );                                                                       
                imgDestroyImage(image);                                                                                                                    
           fileName = nil;                                                                                                                                 
        }else                                                                                                                                              
            {                                                                                                                                              
               //add error file output here                                                                                                                
            }                                                                                                                                              
        //---------------------                                                                                                                            
        filePathName = [[NSBundle mainBundle] pathForResource:@"unit_cube" ofType:@"png"];                                                
        if(fileName != nil)                                                                                                                                
        {                                                                                                                                                  
                image = imgLoadImage([filePathName cStringUsingEncoding:NSASCIIStringEncoding]);                                                           
                glGenTextures(1, &unit_cube_TEXTUREMAP);                                                                                      
                glBindTexture(GL_TEXTURE_2D, unit_cube_TEXTUREMAP);                                                                           
                ConfigureAndLoadTexture(image->data,  image->width, image->height );                                                                       
                imgDestroyImage(image);                                                                                                                    
           fileName = nil;                                                                                                                                 
        }else                                                                                                                                              
            {                                                                                                                                              
               //add error file output here                                                                                                                
            }                                                                                                                                              
        //---------------                                                                                                                                  
        #endif                                                                                                                                             
        //------------------------------------------------------------------------------------------                                                       
        #ifdef WIN32                                                                                                                                       
        loadTexture("_MODEL_FOLDERS_/unit_cube/unit_cube_DOT3.bmp",          unit_cube_NORMALMAP);                
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
        unit_cube_boundingBox[0] = -0.5;
        unit_cube_boundingBox[1] = 0.5;
        unit_cube_boundingBox[2] = -0.5;
        unit_cube_boundingBox[3] = 0.5;
        unit_cube_boundingBox[4] = -0.5;
        unit_cube_boundingBox[5] = 0.5;
        //====================================================================================   
        collisionBoxArray[boxCount][0] = -0.5;
        collisionBoxArray[boxCount][1] = 0.5;
        collisionBoxArray[boxCount][2] = -0.5;
        collisionBoxArray[boxCount][3] = 0.5;
        collisionBoxArray[boxCount][4] = -0.5;
        collisionBoxArray[boxCount][5] = 0.5;
        collisionBoxArray[boxCount][6] = boxCount;
        boxCount++;
