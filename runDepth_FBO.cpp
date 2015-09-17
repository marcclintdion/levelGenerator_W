glEnable(GL_DEPTH_TEST);	

        glBindFramebuffer(GL_FRAMEBUFFER, m_uiFrameBufferObject);   
#ifdef WIN32
        //----------------------------------------------------------------
        glClear (GL_DEPTH_BUFFER_BIT);
        glViewport(1, 1, (GLsizei)viewWidth * 1.2 - 2, (GLsizei)viewHeight - 2);
        //----------------------------------------------------------------
        glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE); 
    
        PerspectiveMatrix(ProjectionShadow, fieldOfView, (GLfloat)viewWidth * 1.2 /  (GLfloat)viewHeight,  adjustNearFar[0],  adjustNearFar[1]);
#endif
   
#ifdef   __APPLE__     
        //----------------------------------------------------------------
        glClear (GL_DEPTH_BUFFER_BIT);
        glViewport(1, 1, 2000 - 2, 1000 - 2);
        //----------------------------------------------------------------
        glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE); 
    
        PerspectiveMatrix(ProjectionShadow, fieldOfView, 2000 / 1000,  adjustNearFar[0],  adjustNearFar[1]);
#endif          
      
        
        //glPolygonOffset(2.5, 10.0);
        //glEnable(GL_POLYGON_OFFSET_FILL);
      
        //================================================================================================================================
        shaderNumber = 47;//shadow_32bit_Stride
        setupTransforms_Shadows();
        #include "_MODEL_FOLDERS_/flowerShield/flowerShield_Shadow_01.cpp"
        //================================================================================================================================
        shaderNumber = 47;//shadow_32bit_Stride
        setupTransforms_Shadows();       
        #include "_MODEL_FOLDERS_/sculptris/sculptris_Shadow_01.cpp"
        //================================================================================================================================
        shaderNumber = 47;//shadow_32bit_Stride
        setupTransforms_Shadows();       
        #include "_MODEL_FOLDERS_/sphere/sphere_Shadow_01.cpp"
        //================================================================================================================================
        shaderNumber = 47;//shadow_32bit_Stride
        setupTransforms_Shadows();      
        #include "_MODEL_FOLDERS_/spiralGear/spiralGear_Shadow_01.cpp"
        //================================================================================================================================
        shaderNumber = 47;//shadow_32bit_Stride
        setupTransforms_Shadows();       
        #include "_MODEL_FOLDERS_/knight/knight_Shadow_01.cpp"
        //================================================================================================================================
        shaderNumber = 47;//shadow_32bit_Stride
        setupTransforms_Shadows();      
        #include "_MODEL_FOLDERS_/blocksEdging/blocksEdging_Shadow_01.cpp"
        //================================================================================================================================
        shaderNumber = 48;//shadow_44bit_Stride
        setupTransforms_Shadows();         
        #include "_MODEL_FOLDERS_/facing_VIEW/facing_VIEW_blocks_01_Shadow_01.cpp"
        //================================================================================================================================
        shaderNumber = 48;//shadow_44bit_Stride        
        setupTransforms_Shadows();         
        #include "_MODEL_FOLDERS_/facing_Sideways_blocks_01/facing_Sideways_blocks_01_Shadow_01.cpp"
        //================================================================================================================================
        shaderNumber = 48;//shadow_44bit_Stride          
        setupTransforms_Shadows();         
        #include "_MODEL_FOLDERS_/facing_UP/facing_UP_blocks_01/facing_UP_blocks_01_Shadow_01.cpp"
        //================================================================================================================================
        shaderNumber = 47;//shadow_32bit_Stride          
        setupTransforms_Shadows();         
        #include "_MODEL_FOLDERS_/pillerPlantPot/pillerPlantPot_Shadow_01.cpp"
        //================================================================================================================================
        shaderNumber = 47;//shadow_32bit_Stride          
        setupTransforms_Shadows();    
        #include "_MODEL_FOLDERS_/plant_v005/plant_v005_Shadow_01.cpp"                                                              
        //====================================================================================                                                                
        shaderNumber = 47;//shadow_32bit_Stride          
        setupTransforms_Shadows();    
        #include "_MODEL_FOLDERS_/chassisFan/chassisFan_Shadow_01.cpp"                                                              
        //====================================================================================                                                                
          
        
        //glEnable(GL_CULL_FACE);


//========================================================================================================================================



//############################################################################################################################################### 
//###############################################################################################################################################   
//###############################################################################################################################################   
        

        glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE); 	                       
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
	
	
	
	
