                    if(unit_cube_NORMALMAP != 0)                                                                                                      
                    {                                                                                                                                              
                            glDeleteTextures(1, &unit_cube_NORMALMAP);                                                                                
                            unit_cube_NORMALMAP = 0;                                                                                                  
                    }                                                                                                                                              
                    if(unit_cube_TEXTUREMAP  != 0)                                                                                                    
                    {                                                                                                                                              
                            glDeleteTextures(1, &unit_cube_TEXTUREMAP);                                                                               
                            unit_cube_TEXTUREMAP  = 0;                                                                                                
                    }                                                                                                                                              
                    if(unit_cube_VBO  != 0)                                                                                                           
                    {                                                                                                                                              
                            glDeleteBuffers(1, &unit_cube_VBO);                                                                                       
                            unit_cube_VBO  = 0;                                                                                                       
                    }                                                                                                                                              
                    if(unit_cube_INDICES_VBO  != 0)                                                                                                   
                    {                                                                                                                                              
                            glDeleteBuffers(1, &unit_cube_INDICES_VBO);                                                                               
                            unit_cube_INDICES_VBO  = 0;                                                                                               
                    }                                                                                                                                              
