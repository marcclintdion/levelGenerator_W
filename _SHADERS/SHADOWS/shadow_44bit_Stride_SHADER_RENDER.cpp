       glUseProgram(SHADER_shadow_44bit_Stride);  
       //-----------------------------------------------------------------------
       MultiplyMatrix(mvpMatrix, ProjectionShadow, LightModelViewMatrix);                    
       //-------------------------------------------------------------------------------------------------------------
                           glVertexAttribPointer(0,   3, GL_FLOAT, GL_FALSE, 44, BUFFER_OFFSET(0));
                           glEnableVertexAttribArray(0);	
                           glVertexAttribPointer(1,   3, GL_FLOAT, GL_FALSE, 44, BUFFER_OFFSET(12));
                           glEnableVertexAttribArray(1);  
                           glVertexAttribPointer(2,   3, GL_FLOAT, GL_FALSE, 44, BUFFER_OFFSET(24));
                           glEnableVertexAttribArray(2);                                                       
                           glVertexAttribPointer(3,   2, GL_FLOAT, GL_FALSE, 44, BUFFER_OFFSET(36));
                           glEnableVertexAttribArray(3);                              
                           //--------------------------------------------------------------------------------------------------
                           glUniformMatrix4fv(UNIFORM_MODELVIEWPROJ_shadow_44bit_Stride, 1, 0,  mvpMatrix);
