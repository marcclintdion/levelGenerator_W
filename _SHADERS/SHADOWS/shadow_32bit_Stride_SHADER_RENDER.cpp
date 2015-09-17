       glUseProgram(SHADER_shadow_32bit_Stride);    
       //-----------------------------------------------------------------------------
       Scale(LightModelViewMatrix, scaleShadowSize, scaleShadowSize, scaleShadowSize);       
       //-----------------------------------------------------------------------------
       MultiplyMatrix(mvpMatrix, ProjectionShadow, LightModelViewMatrix);                                                                                                                         
       //-------------------------------------------------------------------------------------------
                           glVertexAttribPointer(0,   3, GL_FLOAT, GL_FALSE, 32, BUFFER_OFFSET(0));
                           glEnableVertexAttribArray(0);	
                           glVertexAttribPointer(1,   3, GL_FLOAT, GL_FALSE, 32, BUFFER_OFFSET(12));
                           glEnableVertexAttribArray(1);  
                           glVertexAttribPointer(2,   2, GL_FLOAT, GL_FALSE, 32, BUFFER_OFFSET(24));
                           glEnableVertexAttribArray(2);                                                       
                           //-----------------------------------------------------------------------
                           glUniformMatrix4fv(UNIFORM_MODELVIEWPROJ_shadow_32bit_Stride, 1, 0,  mvpMatrix);
