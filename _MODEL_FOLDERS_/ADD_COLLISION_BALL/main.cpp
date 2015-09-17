#include <cstdlib>//__RANDOM
#include <ctime>//____SEED_RANDOM

#include <iostream>
#include <fstream.h>
#include <string.h>

#include <math.h>








                      int  numberOfHitTests            =                            4;
                      char textStringOut_GLOBALS[]     =                   "GLOBALS_4.cpp";
                      char textStringOut_RENDER[]      =                    "RENDER_4.cpp";
                      char textStringOut_Shadows_00[]  =  "drawSpikeyBallShadows_00_4.cpp";                      
                      char textStringOut_Shadows_01[]  =  "drawSpikeyBallShadows_01_4.cpp";

int NUM1 = numberOfHitTests;
int NUM2 = 1;//skips 0 tests; incremented towards ->numberOfHitTests starting with the second ball
int restore_NUM2 = NUM2;


int main(int argc, char *argv[])
{
             srand(time(0));
  
             float randomVelocity[]    = {0.0, 0.0, 0.0};  
             float randomGravity       = 0.0;  

             
             while(randomVelocity[0]   == 0.0)
             {
                  randomVelocity[0]    =  float((rand()% 10)-5) *.01; 
             }
             while(randomVelocity[1]   == 0.0)
             {
                  randomVelocity[1]    =  float((rand()% 10)-5) *.001;              
             }
             while(randomVelocity[2]   == 0.0)
             {
                  randomVelocity[2]    =  float((rand()% 10)-5) *.01;              
             }
             while(randomGravity       == 0.0)
             {
                  randomGravity  =  float( rand()% 10)    *.00015;
             }          
             
             ofstream out_GLOBALS(textStringOut_GLOBALS);
          
            
             out_GLOBALS << "GLfloat     lightPos_spikyBall_00_" << NUM1 << "[]  = {26.75, 102.93, -50.96};"                    << "\n";            
                       
             out_GLOBALS << "GLfloat     lightPos_spikes_00_" << NUM1 << "[]           =  {2.3176, 8.895, 14.04};"              << "\n";  
             out_GLOBALS << "GLfloat     lightAttenuation_spikes_00_" << NUM1 << "     =   3.38642;              "              << "\n";  
             
             out_GLOBALS << "GLfloat     lightAttenuation_spikyBall_00_"     << NUM1  << "   =  1.283;"                         << "\n";             
             out_GLOBALS << "GLfloat     spikyBall_00_" << NUM1  << "_position[]  = {0.5, 0.5, 0.5};"                           << "\n";
             out_GLOBALS << "GLfloat     spinBall_"     << NUM1  << "             =  0.0;"                                      << "\n";     
             out_GLOBALS << "GLfloat     spinVelocity_" << NUM1  << "             =  1.0;"                                       << "\n";  
             out_GLOBALS << "GLfloat     radius_"       << NUM1  << "             =  0.125;"                                    << "\n";    
             out_GLOBALS << "GLfloat     spikyBall_00_" << NUM1  << "_Velocity[]  = {" << randomVelocity[0] << ", " << randomVelocity[1] << ", " << randomVelocity[2] << "};"                       << "\n";     
             out_GLOBALS << "GLfloat     spinX_Ball_"   << NUM1  << "             = 0.0;"                                       << "\n";             
             out_GLOBALS << "GLfloat     spinZ_Ball_"   << NUM1  << "             = 0.0;"                                       << "\n"; 
             
             out_GLOBALS << "GLfloat     velocityIncreaseRotation_" << NUM1  << "     = 1.0;                  "                     << "\n";
             out_GLOBALS << "GLfloat     velocitySwap_" << NUM1  << "[]               = {0.0, 0.0, 0.0, 0.0}; "                     << "\n";             
             out_GLOBALS << "//----------                                               "                                       << "\n";
             out_GLOBALS << "GLfloat     flyingSpikyBallShadowPosition_00_" << NUM1  << "[] =  {-0.05, 0.27, -11.4};"           << "\n";
             out_GLOBALS << "GLfloat     flyingSpikyBallShadowRotation_00_" << NUM1  << "[] =  { 1.0, 1.0, 1.0, 0.0};"          << "\n";
             out_GLOBALS << "GLfloat     scaleFlyingSpikyBallShadow_00_" << NUM1  << "         = 1.2;              "            << "\n";
             out_GLOBALS << "//----------"                       << "\n";
             out_GLOBALS << "GLfloat     flyingSpikyBallShadowPosition_01_" << NUM1  << "[] =   {0.198, 0.470997, -11.7171};"   << "\n";
             out_GLOBALS << "GLfloat     flyingSpikyBallShadowRotation_01_" << NUM1  << "[] =  { 1.0, 1.0, 1.0, 0.0};"          << "\n";
             out_GLOBALS << "GLfloat     scaleFlyingSpikyBallShadow_01_" << NUM1  << "      =    1.5;               "           << "\n";
             
             out_GLOBALS << "//``````````````````````````````````````````````"                                                  << "\n\n";             
             for(int i = 0; i < numberOfHitTests-1; i++)
             {
                  out_GLOBALS << "GLfloat     distance_" << NUM1 << "_" << NUM2++ << "=  0.0;"                                  << "\n";              
             }
             out_GLOBALS << "//``````````````````````````````````````````````"                                                  << "\n";     
         NUM2 = restore_NUM2;              
             out_GLOBALS << "///////=========================================================   "                               << "\n";             
             for(int i = 0; i < numberOfHitTests-1; i++)
             {
                  out_GLOBALS << "GLfloat     SWIZZLE_Velocity_" << NUM1 << "_" << NUM2++ << "[]       = {0.0, 0.0, 0.0};"      << "\n";              
             }
             out_GLOBALS << "///////=========================================================   "                               << "\n";     
                      
         NUM2 = restore_NUM2;              
              out_GLOBALS << "/////////----------------------------------------------   "                                       << "\n";             
             for(int i = 0; i < numberOfHitTests-1; i++)
             {
                  out_GLOBALS << "GLfloat     spikyBall_00_" << NUM1 << "_" << NUM2++ << "_vector[]       = {0.0, 0.0, 0.0};"   << "\n";              
             }
             out_GLOBALS << "/////////----------------------------------------------   "                                        << "\n";     
    
         NUM2 = restore_NUM2;              
             out_GLOBALS << "////------------------////"       << "\n";             
             for(int i = 0; i < numberOfHitTests-1; i++)
             {
                  out_GLOBALS << "bool collision_" << NUM1 << "_" << NUM2++ << "        = false;"                               << "\n";              
             }
             out_GLOBALS << "////------------------////"       << "\n";     
////////////////////////////////////////////_____GLOBALS______////////////////////////////////////////////
////////////////////////////////////////////_____GLOBALS______////////////////////////////////////////////
////////////////////////////////////////////_____GLOBALS______////////////////////////////////////////////
////////////////////////////////////////////_____RENDER______////////////////////////////////////////////   
////////////////////////////////////////////_____RENDER______////////////////////////////////////////////  
////////////////////////////////////////////_____RENDER______////////////////////////////////////////////      
    ofstream out_RENDER(textStringOut_RENDER); 
 
             out_RENDER << "//------------------------------------------------------"                                           << "\n\n"; 
             out_RENDER << "if(spikyBall_00_" << NUM1 << "_position[0] <= -2.50)///leftWall_Collision"                          << "\n"; 
             out_RENDER << "{"                                                                                                  << "\n"; 
             out_RENDER << "        spikyBall_00_" << NUM1 << "_Velocity[0] *= -1;"                                             << "\n"; 
             out_RENDER << "}"                                                                                                  << "\n"; 
             out_RENDER << "if(spikyBall_00_" << NUM1 << "_position[0] >= 2.50)////rightWall_Collision"                         << "\n"; 
             out_RENDER << "{"                                                                                                  << "\n"; 
             out_RENDER << "        spikyBall_00_" << NUM1 << "_Velocity[0] *= -1;"                                             << "\n"; 
             out_RENDER << "}                                                        "                                          << "\n\n";               
             out_RENDER << "//------------------------------------------------------"                                           << "\n\n";             
             out_RENDER << "if(spikyBall_00_" << NUM1 << "_position[1] < .35)///floor_Collision"                                 << "\n"; 
             out_RENDER << "{"                                                                                                  << "\n"; 
             out_RENDER << "        spikyBall_00_" << NUM1 << "_Velocity[1] *= -1;"                                             << "\n"; 
             out_RENDER << "}"                                                                                                  << "\n\n"; 
             out_RENDER << "//------------------------------------------------------"                                           << "\n\n";
             out_RENDER << "if(spikyBall_00_" << NUM1 << "_position[2] <= -2.50)///farWall_Collision"                           << "\n"; 
             out_RENDER << "{"                                                                                                  << "\n"; 
             out_RENDER << "        spikyBall_00_" << NUM1 << "_Velocity[2] *= -1;"                                             << "\n"; 
             out_RENDER << "}"                                                                                                  << "\n"; 
             out_RENDER << "if(spikyBall_00_" << NUM1 << "_position[2] >= 2.50)////nearWall_Collision"                          << "\n"; 
             out_RENDER << "{"                                                                                                  << "\n"; 
             out_RENDER << "        spikyBall_00_" << NUM1 << "_Velocity[2] *= -1;"                                             << "\n"; 
             out_RENDER << "}                                                   "                                               << "\n\n";           
             out_RENDER << "//------------------------------------------------------"                                           << "\n"; 
    
        NUM2 = restore_NUM2;      
    
                                                                                                 
             for(int i = 0; i < numberOfHitTests-1; i++)
             {             
                           out_RENDER << "                      ///___" << NUM1 << "_" << NUM2 << "___//"    << "\n";                         
                           out_RENDER << "spikyBall_00_" << NUM1 << "_" << NUM2 << "_vector[0] = spikyBall_00_" << NUM2 << "_position[0] - spikyBall_00_" << NUM1 << "_position[0];" << "\n";  
                           out_RENDER << "spikyBall_00_" << NUM1 << "_" << NUM2 << "_vector[1] = spikyBall_00_" << NUM2 << "_position[1] - spikyBall_00_" << NUM1 << "_position[1];" << "\n";                           
                           out_RENDER << "spikyBall_00_" << NUM1 << "_" << NUM2 << "_vector[2] = spikyBall_00_" << NUM2 << "_position[2] - spikyBall_00_" << NUM1 << "_position[2];" << "\n";                                                                       
                          
                           out_RENDER << "distance_" << NUM1 << "_" << NUM2 << "          = sqrt(((spikyBall_00_" << NUM1 << "_" << NUM2 << "_vector[0])*(spikyBall_00_" << NUM1 << "_" << NUM2 << "_vector[0]))"  << "\n";  
                           out_RENDER << "                                                     + ((spikyBall_00_" << NUM1 << "_" << NUM2 << "_vector[1])*(spikyBall_00_" << NUM1 << "_" << NUM2 << "_vector[1]))" << "\n"; 
                           out_RENDER << "                                                     + ((spikyBall_00_" << NUM1 << "_" << NUM2 << "_vector[2])*(spikyBall_00_" << NUM1 << "_" << NUM2 << "_vector[2])));" << "\n";                                                                                 
                           out_RENDER << "                                                     ///___" << NUM1 << "_" << NUM2++ << "___//"  << "\n\n";             
             }
       
    
    
    

        NUM2 = restore_NUM2;             
             
             for(int i = 0; i < numberOfHitTests-1; i++)
             {                                         
                  out_RENDER << "//////////////////___" << NUM1 << "_" << NUM2 << "___////////////////////////////////////////////////      "    << "\n";                                 
                  out_RENDER << "if(distance_" << NUM1 << "_" << NUM2 << " <= radius_" << NUM1 << "+radius_" << NUM2 << " && !collision_" << NUM1 << "_" << NUM2 << ")"    << "\n"; 
                  out_RENDER << " {                                     "                                                                        << "\n";                   
                  out_RENDER << "     SWIZZLE_Velocity_" << NUM1 << "_" << NUM2 << "[0]   = spikyBall_00_" << NUM2 << "_Velocity[0];"    << "\n"; 
                  out_RENDER << "     SWIZZLE_Velocity_" << NUM1 << "_" << NUM2 << "[1]   = spikyBall_00_" << NUM2 << "_Velocity[1];"    << "\n"; 
                  out_RENDER << "     SWIZZLE_Velocity_" << NUM1 << "_" << NUM2 << "[2]   = spikyBall_00_" << NUM2 << "_Velocity[2];//__radial_Collision"    << "\n\n"; 

                  out_RENDER << "     spikyBall_00_" << NUM2 << "_Velocity[0] = spikyBall_00_" << NUM1 << "_Velocity[0];                              "    << "\n";        
                  out_RENDER << "     spikyBall_00_" << NUM2 << "_Velocity[1] = spikyBall_00_" << NUM1 << "_Velocity[1];                              "    << "\n";        
                  out_RENDER << "     spikyBall_00_" << NUM2 << "_Velocity[2] = spikyBall_00_" << NUM1 << "_Velocity[2];"    << "\n\n"; 
                  
                  out_RENDER << "     spikyBall_00_" << NUM1 << "_Velocity[0] = SWIZZLE_Velocity_" << NUM1 << "_" << NUM2 << "[0];"    << "\n"; 
                  out_RENDER << "     spikyBall_00_" << NUM1 << "_Velocity[1] = SWIZZLE_Velocity_" << NUM1 << "_" << NUM2 << "[1];"    << "\n"; 
                  out_RENDER << "     spikyBall_00_" << NUM1 << "_Velocity[2] = SWIZZLE_Velocity_" << NUM1 << "_" << NUM2 << "[2];                  "    << "\n\n"; 
                  
                  out_RENDER << "     collision_" << NUM1 << "_" << NUM2 << " = true;                               "    << "\n";         
                  out_RENDER << "}                                     "    << "\n\n"; 
                  
                  out_RENDER << "if(distance_" << NUM1 << "_" << NUM2 << " > radius_" << NUM1 << "+radius_" << NUM2 << " && collision_" << NUM1 << "_" << NUM2 << ")"    << "\n"; 
                  out_RENDER << "{"    << "\n"; 
                  out_RENDER << "      collision_" << NUM1 << "_" << NUM2 << " = false; "    << "\n"; 
                  out_RENDER << "} "    << "\n"; 
                  out_RENDER << "//////////////////___" << NUM1 << "_" << NUM2++ << "___////////////////////////////////////////////////     "    << "\n\n";                                                                     
             }                                                       
                                                       
                                                       
             out_RENDER << " //***************************************************************   "    << "\n";           
             out_RENDER << "//__" << NUM1 << "__//                                                //__" << NUM1 << "__// "    << "\n"; 
             out_RENDER << "         spikyBall_00_" << NUM1 << "_position[0] += spikyBall_00_" << NUM1 << "_Velocity[0];"    << "\n"; 
             out_RENDER << "         spikyBall_00_" << NUM1 << "_position[1] += spikyBall_00_" << NUM1 << "_Velocity[1];"    << "\n"; 
             out_RENDER << "         spikyBall_00_" << NUM1 << "_position[2] += spikyBall_00_" << NUM1 << "_Velocity[2];    "    << "\n"; 
             out_RENDER << "//__" << NUM1 << "__//                                                //__" << NUM1 << "__//    "    << "\n";                   
             out_RENDER << "//***************************************************************  "    << "\n"; 


             out_RENDER << "              glTranslatef(spikyBall_00_" << NUM1 << "_position[0],spikyBall_00_" << NUM1 << "_position[1],spikyBall_00_" << NUM1 << "_position[2]);"    << "\n"; 
             out_RENDER << "              spinBall_" << NUM1 << " += 1;                                                                  "    << "\n";   
             out_RENDER << "              spinX_Ball_" << NUM1 << " =  spikyBall_00_" << NUM1 << "_Velocity[2];//+.000000001 <----Used to prevent scaling @ zeroVelocity"    << "\n"; 
             out_RENDER << "              spinZ_Ball_" << NUM1 << " = -spikyBall_00_" << NUM1 << "_Velocity[0]-.000000001;"    << "\n\n"; 
                                                                    
             out_RENDER << "              if(spikyBall_00_" << NUM1 << "_Velocity[0] == 0 && spikyBall_00_" << NUM1 << "_Velocity[1] == 0 && spikyBall_00_" << NUM1 << "_Velocity[2] == 0)"    << "\n"; 
             out_RENDER << "              {"    << "\n"; 
             out_RENDER << "                     spinBall_" << NUM1 << " = 0;"    << "\n"; 
             out_RENDER << "              }"    << "\n\n\n"; 
                                                                                        
             out_RENDER << "              spikyBall_00_" << NUM1 << "_Velocity[1]  -= " << randomGravity << " + spikyBall_00_" << NUM1 << "_Velocity[1]*spikyBall_00_" << NUM1 << "_Velocity[1];//_RANDOM_GRAVITY "    << "\n\n\n";              
             
             
             out_RENDER << "              velocitySwap_" << NUM1 << "[0] = spikyBall_00_" << NUM1 << "_Velocity[0];                           "    << "\n"; 
             out_RENDER << "              velocitySwap_" << NUM1 << "[2] = spikyBall_00_" << NUM1 << "_Velocity[2];                           "    << "\n\n\n";          
              
             out_RENDER << "              if(velocitySwap_" << NUM1 << "[0] < 0.0)                                               "    << "\n"; 
             out_RENDER << "              {                                                                         "    << "\n"; 
             out_RENDER << "                     velocitySwap_" << NUM1 << "[0] *= -1.0;                                           "    << "\n"; 
             out_RENDER << "              }                                                                         "    << "\n"; 
             out_RENDER << "              if(velocitySwap_" << NUM1 << "[2] < 0.0)                                               "    << "\n"; 
             out_RENDER << "              {                                                                         "    << "\n"; 
             out_RENDER << "                     velocitySwap_" << NUM1 << "[2] *= -1.0;                                           "    << "\n"; 
             out_RENDER << "              }                                                                         "    << "\n\n"; 
              
             out_RENDER << "              velocityIncreaseRotation_" << NUM1 << " = (velocitySwap_" << NUM1 << "[0] + velocitySwap_" << NUM1 << "[2])*100; "    << "\n\n"; 

             out_RENDER << "              spinBall_" << NUM1 << " += velocityIncreaseRotation_" << NUM1 << ";                                 "    << "\n\n";            
             
             out_RENDER << "              glRotatef(spinBall_" << NUM1 << "*spinVelocity_" << NUM1 << ", spinX_Ball_" << NUM1 << ", 0, spinZ_Ball_" << NUM1 << ");"    << "\n\n"; 
             out_RENDER << "            //  glPushMatrix();"    << "\n"; 
             out_RENDER << "            //         glLoadIdentity(); "    << "\n"; 
             out_RENDER << "            //         glRotatef(-spinBall_" << NUM1 << "*spinVelocity_" << NUM1 << ", -spinX_Ball_" << NUM1 << ", 0, spinZ_Ball_" << NUM1 << "); "    << "\n"; 
             out_RENDER << "            //         glLightfv (GL_LIGHT0,GL_POSITION, lightPos_spikyBall_00_" << NUM1 << ");"    << "\n"; 
             out_RENDER << "            //         glLightf (GL_LIGHT0, GL_QUADRATIC_ATTENUATION, lightAttenuation_spikyBall_00_" << NUM1 << ");       "    << "\n";                                                               
             out_RENDER << "            //  glPopMatrix();                                                                    "    << "\n\n"; 




ofstream out_Shadows_01(textStringOut_Shadows_01); 


     out_Shadows_01 <<"glPushMatrix();       "    << "\n";       
     
     
     out_Shadows_01 <<"     glColor4f(spikyBall_00_" << NUM1 << "_position[1] * scaleFlyingSpikeyBallHeightFade * scaleFlyingSpikeyBallHeightFade+.3, spikyBall_00_" << NUM1 << "_position[1] * scaleFlyingSpikeyBallHeightFade * scaleFlyingSpikeyBallHeightFade+.3, spikyBall_00_" << NUM1 << "_position[1] * scaleFlyingSpikeyBallHeightFade * scaleFlyingSpikeyBallHeightFade+.3, 1.0);"    << "\n"; 
     out_Shadows_01 <<"     //-----------------------------------------------------------------------------------------------------------------------------------------------------------"    << "\n"; 
     out_Shadows_01 <<"     glTranslatef(moveSet[0], -moveSet[2], 0.0f);"    << "\n"; 
     out_Shadows_01 <<"     glTranslatef(flyingSpikyBallShadowPosition_01_" << NUM1 << "[0]+spikyBall_00_" << NUM1 << "_position[0], flyingSpikyBallShadowPosition_01_" << NUM1 << "[1]-spikyBall_00_" << NUM1 << "_position[2], flyingSpikyBallShadowPosition_01_" << NUM1 << "[2]);"    << "\n"; 
     out_Shadows_01 <<"     glScalef(1.0+spikyBall_00_" << NUM1 << "_position[1]*scaleFlyingSpikyBallShadow_01_" << NUM1 << "*scaleFlyingSpikyBallShadow_01_" << NUM1 << ", 1.0+spikyBall_00_" << NUM1 << "_position[1]*scaleFlyingSpikyBallShadow_01_" << NUM1 << "*scaleFlyingSpikyBallShadow_01_" << NUM1 << ", 1.0+spikyBall_00_" << NUM1 << "_position[1]*scaleFlyingSpikyBallShadow_01_" << NUM1 << "*scaleFlyingSpikyBallShadow_01_" << NUM1 << ");"    << "\n"; 
     out_Shadows_01 <<"     glRotatef(spinBall_" << NUM1 << ", spinX_Ball_" << NUM1 << ", 0, spinZ_Ball_" << NUM1 << ");         "    << "\n"; 
     out_Shadows_01 <<"     //-----------------------------------------------------------------------------------------------------------------------------------------------------------"    << "\n"; 
           
     out_Shadows_01 <<"     #include \"_MODEL_FOLDERS_/spikyBalls/drawSpikeyBallShadowsModel.cpp\""    << "\n"; 
           
     out_Shadows_01 <<"     //-----------------------------------------------------------------------------------------------------------------------------------------------------------"    << "\n"; 
     out_Shadows_01 <<"     glColor4f(spikyBall_00_" << NUM1 << "_position[1] * scaleFlyingSpikeyBallHeightFade * scaleFlyingSpikeyBallHeightFade+.3, spikyBall_00_" << NUM1 << "_position[1] * scaleFlyingSpikeyBallHeightFade * scaleFlyingSpikeyBallHeightFade+.3, spikyBall_00_" << NUM1 << "_position[1] * scaleFlyingSpikeyBallHeightFade * scaleFlyingSpikeyBallHeightFade+.3, 1.0);"    << "\n"; 
     out_Shadows_01 <<"glPopMatrix();"    << "\n"; 

     out_Shadows_01 <<"/////////////////////////////////////////////////////////////////////////////////////////////////////////////////"    << "\n"; 
     out_Shadows_01 <<"                                          //-----------------------------"    << "\n"; 
     out_Shadows_01 <<"                                                  glLoadIdentity();"    << "\n"; 
     out_Shadows_01 <<"                                          //-----------------------------"    << "\n"; 
     out_Shadows_01 <<"///////////////////////////////////////////////////////////////////////////////////////////////////////////////// "    << "\n"; 

ofstream out_Shadows_00(textStringOut_Shadows_00); 


     out_Shadows_00 <<"glPushMatrix();       "    << "\n";       
     
     
     out_Shadows_00 <<"     glColor4f(spikyBall_00_" << NUM1 << "_position[1] * scaleFlyingSpikeyBallHeightFade * scaleFlyingSpikeyBallHeightFade, spikyBall_00_" << NUM1 << "_position[1] * scaleFlyingSpikeyBallHeightFade * scaleFlyingSpikeyBallHeightFade, spikyBall_00_" << NUM1 << "_position[1] * scaleFlyingSpikeyBallHeightFade * scaleFlyingSpikeyBallHeightFade, 1.0);"    << "\n"; 
     out_Shadows_00 <<"     //-----------------------------------------------------------------------------------------------------------------------------------------------------------"    << "\n"; 
     out_Shadows_00 <<"     glTranslatef(moveSet[0], -moveSet[2], 0.0f);"    << "\n"; 
     out_Shadows_00 <<"     glTranslatef(flyingSpikyBallShadowPosition_00_" << NUM1 << "[0]+spikyBall_00_" << NUM1 << "_position[0], flyingSpikyBallShadowPosition_00_" << NUM1 << "[1]-spikyBall_00_" << NUM1 << "_position[2], flyingSpikyBallShadowPosition_00_" << NUM1 << "[2]);"    << "\n"; 
     out_Shadows_00 <<"     glScalef(1.0+spikyBall_00_" << NUM1 << "_position[1]*scaleFlyingSpikyBallShadow_00_" << NUM1 << "*scaleFlyingSpikyBallShadow_00_" << NUM1 << ", 1.0+spikyBall_00_" << NUM1 << "_position[1]*scaleFlyingSpikyBallShadow_00_" << NUM1 << "*scaleFlyingSpikyBallShadow_00_" << NUM1 << ", 1.0+spikyBall_00_" << NUM1 << "_position[1]*scaleFlyingSpikyBallShadow_00_" << NUM1 << "*scaleFlyingSpikyBallShadow_00_" << NUM1 << ");"    << "\n"; 
     out_Shadows_00 <<"     glRotatef(spinBall_" << NUM1 << ", spinX_Ball_" << NUM1 << ", 0, spinZ_Ball_" << NUM1 << ");         "    << "\n"; 
     out_Shadows_00 <<"     //-----------------------------------------------------------------------------------------------------------------------------------------------------------"    << "\n"; 
           
     out_Shadows_00 <<"     #include \"_MODEL_FOLDERS_/spikyBalls/drawSpikeyBallShadowsModel.cpp\""    << "\n"; 
           
     out_Shadows_00 <<"     //-----------------------------------------------------------------------------------------------------------------------------------------------------------"    << "\n"; 
     out_Shadows_00 <<"     glColor4f(spikyBall_00_" << NUM1 << "_position[1] * scaleFlyingSpikeyBallHeightFade * scaleFlyingSpikeyBallHeightFade+.3, spikyBall_00_" << NUM1 << "_position[1] * scaleFlyingSpikeyBallHeightFade * scaleFlyingSpikeyBallHeightFade+.3, spikyBall_00_" << NUM1 << "_position[1] * scaleFlyingSpikeyBallHeightFade * scaleFlyingSpikeyBallHeightFade+.3, 1.0);"    << "\n"; 
     out_Shadows_00 <<"glPopMatrix();"    << "\n"; 

     out_Shadows_00 <<"/////////////////////////////////////////////////////////////////////////////////////////////////////////////////"    << "\n"; 
     out_Shadows_00 <<"                                          //-----------------------------"    << "\n"; 
     out_Shadows_00 <<"                                                  glLoadIdentity();"    << "\n"; 
     out_Shadows_00 <<"                                          //-----------------------------"    << "\n"; 
     out_Shadows_00 <<"///////////////////////////////////////////////////////////////////////////////////////////////////////////////// "    << "\n"; 

    return 0;
}








