
   MultiplyMatrix(mvpMatrix, projection, modelView);
    //----------------------------------------------------------------------------------------------------------
    LoadIdentity(lightMatrix);
    InvertMatrix(lightMatrix, modelView);
    //----------------------------------------------------------------------------------------------------------
    LoadIdentity(textureMatrix);
    //Translate(textureMatrix, shadowsPositionOffset[0], shadowsPositionOffset[1], shadowsPositionOffset[2]);
    //Scale(textureMatrix, scaleShadows, scaleShadows, scaleShadows);
 
 
 
 glUseProgram(leaves_A_SHADER);
          //------------------------------------------------------------------------------
          glVertexAttribPointer(0,     3, GL_FLOAT, GL_FALSE, 32, BUFFER_OFFSET(0));
          glEnableVertexAttribArray(0);
          glVertexAttribPointer(1,     3, GL_FLOAT, GL_FALSE, 32, BUFFER_OFFSET(12));
          glEnableVertexAttribArray(1);
          glVertexAttribPointer(2,     2, GL_FLOAT, GL_FALSE, 32, BUFFER_OFFSET(24));
          glEnableVertexAttribArray(2);
          //------------------------------------------------------------------------------------------------
          glUniform4f(UNIFORM_LIGHT_POSITION_01_leaves_A,              leaves_A_LIGHT_POSITION_01[0],
                                                                       leaves_A_LIGHT_POSITION_01[1],
                                                                       leaves_A_LIGHT_POSITION_01[2],
                                                                       leaves_A_LIGHT_POSITION_01[3]);
           
          glUniform4f(UNIFORM_offset_leaves_A,                         offset[0],
                                                                       offset[1],
                                                                       offset[2],
                                                                       offset[3]);
                                                                                                       
          glUniform4f(UNIFORM_tileJump_leaves_A,                       tileJump_leaves_A[0],
                                                                       tileJump_leaves_A[1],
                                                                       tileJump_leaves_A[2],
                                                                       tileJump_leaves_A[3]);
         
          glUniform1f(UNIFORM_shininess_leaves_A,                  shininess_leaves_A);
          glUniform1f(UNIFORM_ambient_leaves_A,                    ambient_leaves_A);
          glUniform1f(UNIFORM_counter_leaves_A,                    globalLinearAttenuation);
          //------------------------------------------------------------------------------------------------
          glUniformMatrix4fv(UNIFORM_MODELVIEW_leaves_A,       1, 0,         modelView);
          glUniformMatrix4fv(UNIFORM_MODELVIEWPROJ_leaves_A,   1, 0,         mvpMatrix);
          //---------------     
          glUniformMatrix4fv(UNIFORM_viewMatrix_leaves_A,      1, 0,         viewMatrix);
          //---------------     
          glUniformMatrix4fv(UNIFORM_SHADOW_PROJ_leaves_A,     1, 0,         ProjectionShadow);
          glUniformMatrix4fv(UNIFORM_modelViewShadow_leaves_A, 1, 0,         modelViewShadow);
          //---------------
          glUniformMatrix4fv(UNIFORM_LIGHT_MATRIX_leaves_A,    1, 0,         lightMatrix);
          glUniformMatrix4fv(UNIFORM_TEXTURE_MATRIX_leaves_A,  1, 0,         textureMatrix);
          //-------------------------------------------------------------------------------------------------
          glUniform1i(UNIFORM_ShadowTexture_leaves_A,  3);
          glUniform1i(UNIFORM_TEXTURE_DOT3_leaves_A,   1);
          glUniform1i(UNIFORM_TEXTURE_leaves_A,        0);
    //====================================================================================================================

//---------------------------------------------------------------
glActiveTexture ( GL_TEXTURE3 );                                                                                                                                          
glBindTexture(GL_TEXTURE_2D, m_uiShadowMapTexture);                                                                                                                          
//---  
