#include <string.h>
#include <fstream.h>
using namespace std;
int main() 
{
    ifstream in_TEX( "piller_00_TEX.cpp"); 
    ifstream in_NORM("piller_00_NORM.cpp");     
    ifstream in_VERT("piller_00_VERT.cpp");     
   
    ofstream out("piller_00.cpp"); 
    
    out << "GLfloat piller_00[] = \n { \n";
    
    string vert;
    string norm;    
    string tex;    
    
    float skipVert = 0;
    float skipNorm = 0;
    float skipTex = 0;    
       
   
   
   getline(in_VERT, vert);
   getline(in_NORM, norm);   
   getline(in_TEX,  tex);        
  
            getline(in_VERT, vert);
            getline(in_NORM, norm);
            getline(in_TEX,  tex);  
  
  
   bool breakLoop = false;  
        
        
   for(int i = 0; i < 1140 * 1.333; i++)
   {
            getline(in_VERT, vert);
            getline(in_NORM, norm);
            getline(in_TEX,  tex);
            

            if(vert == "};")
            {
                    breakLoop = true;
                    out << "";
            }
            else
            {
                    out << vert << norm << tex << endl;
                    
            }
            
            if(breakLoop)
            {
                 i += 100000;
            }

   }        
        out << "\n};\n";
           
   
/*   
    while(getline(in_VERT, vert)) 
    {
       
        if(vert == "{")
        {
            out << " \n";
        }
              
        else
        {
            out << vert << "\n";
        }
        
          
    }    
   
    while(getline(in_NORM, norm)) 
    {
       
        if(norm == "{")
        {
            out << " \n";
        }
        else
        {     
            out << norm << "\n";
        }
    
    
     }    
    
     while(getline(in_TEX, tex)) 
     {
        
        if(tex == "{")
        {
            out << " \n";
        }
        else
        {
            out << tex << "\n";
        }
     
    
     }
    
    skipVert = 0;
    skipNorm = 0;
    skipTex = 0;        
*/    
    
}
