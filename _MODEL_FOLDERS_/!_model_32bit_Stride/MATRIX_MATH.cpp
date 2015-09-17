void Scale(float* mtx, float xScale, float yScale, float zScale)
{ 
        // [ 0 4  8 12 ]   [ x 0 0 0 ]
        // [ 1 5  9 13 ] x [ 0 y 0 0 ] 
        // [ 2 6 10 14 ]   [ 0 0 z 0 ]
        // [ 3 7 11 15 ]   [ 0 0 0 1 ]   
	
	mtx[ 0] *= xScale;
	mtx[ 4] *= yScale;
	mtx[ 8] *= zScale;
	
	mtx[ 1] *= xScale;
	mtx[ 5] *= yScale;
	mtx[ 9] *= zScale;
	
	mtx[ 2] *= xScale;
	mtx[ 6] *= yScale;
	mtx[10] *= zScale;
	
	mtx[ 3] *= xScale;
	mtx[ 7] *= yScale;
	mtx[11] *= xScale;
}

//=================================================================================================================================



void PerspectiveMatrix(float *m, float fov, float aspect, float zNear, float zFar)
{
    const float h = 1.0f/tan(fov * 0.0087266);
    float neg_depth = zNear-zFar;
    
    m[0] = h / aspect;
    m[1] = 0;
    m[2] = 0;
    m[3] = 0;
    
    m[4] = 0;
    m[5] = h;
    m[6] = 0;
    m[7] = 0;
    
    m[8] = 0;
    m[9] = 0;
    m[10] = (zFar + zNear)/neg_depth;
    m[11] = -1;
    
    m[12] = 0;
    m[13] = 0;
    m[14] = 2.0f*(zNear*zFar)/neg_depth;
    m[15] = 0;
}
//=================================================================================================================================


void LoadIdentity(float* mtx)
{
	// [ 0 4  8 12 ]
	// [ 1 5  9 13 ]
	// [ 2 6 10 14 ]
    // [ 3 7 11 15 ]
	mtx[ 0] = mtx[ 5] = mtx[10] = mtx[15] = 1.0f;
	
	mtx[ 1] = mtx[ 2] = mtx[ 3] = mtx[ 4] =    
	mtx[ 6] = mtx[ 7] = mtx[ 8] = mtx[ 9] =    
	mtx[11] = mtx[12] = mtx[13] = mtx[14] = 0.0;
}

//=================================================================================================================================


void MultiplyMatrix(float* ret, const float* lhs, const float* rhs)
{
	// [ 0 4  8 12 ]   [ 0 4  8 12 ]
	// [ 1 5  9 13 ] x [ 1 5  9 13 ]
	// [ 2 6 10 14 ]   [ 2 6 10 14 ]
	// [ 3 7 11 15 ]   [ 3 7 11 15 ]
	ret[ 0] = lhs[ 0]*rhs[ 0] + lhs[ 4]*rhs[ 1] + lhs[ 8]*rhs[ 2] + lhs[12]*rhs[ 3];
	ret[ 1] = lhs[ 1]*rhs[ 0] + lhs[ 5]*rhs[ 1] + lhs[ 9]*rhs[ 2] + lhs[13]*rhs[ 3];
	ret[ 2] = lhs[ 2]*rhs[ 0] + lhs[ 6]*rhs[ 1] + lhs[10]*rhs[ 2] + lhs[14]*rhs[ 3];
	ret[ 3] = lhs[ 3]*rhs[ 0] + lhs[ 7]*rhs[ 1] + lhs[11]*rhs[ 2] + lhs[15]*rhs[ 3];
    
	ret[ 4] = lhs[ 0]*rhs[ 4] + lhs[ 4]*rhs[ 5] + lhs[ 8]*rhs[ 6] + lhs[12]*rhs[ 7];
	ret[ 5] = lhs[ 1]*rhs[ 4] + lhs[ 5]*rhs[ 5] + lhs[ 9]*rhs[ 6] + lhs[13]*rhs[ 7];
	ret[ 6] = lhs[ 2]*rhs[ 4] + lhs[ 6]*rhs[ 5] + lhs[10]*rhs[ 6] + lhs[14]*rhs[ 7];
	ret[ 7] = lhs[ 3]*rhs[ 4] + lhs[ 7]*rhs[ 5] + lhs[11]*rhs[ 6] + lhs[15]*rhs[ 7];
    
	ret[ 8] = lhs[ 0]*rhs[ 8] + lhs[ 4]*rhs[ 9] + lhs[ 8]*rhs[10] + lhs[12]*rhs[11];
	ret[ 9] = lhs[ 1]*rhs[ 8] + lhs[ 5]*rhs[ 9] + lhs[ 9]*rhs[10] + lhs[13]*rhs[11];
	ret[10] = lhs[ 2]*rhs[ 8] + lhs[ 6]*rhs[ 9] + lhs[10]*rhs[10] + lhs[14]*rhs[11];
	ret[11] = lhs[ 3]*rhs[ 8] + lhs[ 7]*rhs[ 9] + lhs[11]*rhs[10] + lhs[15]*rhs[11];
    
	ret[12] = lhs[ 0]*rhs[12] + lhs[ 4]*rhs[13] + lhs[ 8]*rhs[14] + lhs[12]*rhs[15];
	ret[13] = lhs[ 1]*rhs[12] + lhs[ 5]*rhs[13] + lhs[ 9]*rhs[14] + lhs[13]*rhs[15];
	ret[14] = lhs[ 2]*rhs[12] + lhs[ 6]*rhs[13] + lhs[10]*rhs[14] + lhs[14]*rhs[15];
	ret[15] = lhs[ 3]*rhs[12] + lhs[ 7]*rhs[13] + lhs[11]*rhs[14] + lhs[15]*rhs[15];
}

void AssignMatrix(GLfloat* out, const GLfloat* in)
{
    out[0]  = in[0];
    out[1]  = in[1];      
    out[2]  = in[2];      
    out[3]  = in[3];      
    out[4]  = in[4];
    out[5]  = in[5];      
    out[6]  = in[6];      
    out[7]  = in[7]; 
    out[8]  = in[8];
    out[9]  = in[9];      
    out[10] = in[10];      
    out[11] = in[11];    
    out[12] = in[12];      
    out[13] = in[13];       
    out[14] = in[14];      
    out[15] = in[15];          
}     
//=================================================================================================================================

void RotateX(float* mtx, float deg)
{
	// [ 0 4  8 12 ]   [ 1  0    0  0 ]
	// [ 1 5  9 13 ] x [ 0 cos -sin 0 ]
	// [ 2 6 10 14 ]   [ 0 sin  cos 0 ]
	// [ 3 7 11 15 ]   [ 0  0    0  1 ]
	
	float rad = deg * (M_PI/180.0f);
	
	float cosrad = cosf(rad);
	float sinrad = sinf(rad);
	
	float mtx04 = mtx[4];
	float mtx05 = mtx[5];
	float mtx06 = mtx[6];
	float mtx07 = mtx[7];
	
	mtx[ 4] = mtx[ 8]*sinrad + mtx04*cosrad;
	mtx[ 8] = mtx[ 8]*cosrad - mtx04*sinrad;
	
	mtx[ 5] = mtx[ 9]*sinrad + mtx05*cosrad;
	mtx[ 9] = mtx[ 9]*cosrad - mtx05*sinrad;
	
	mtx[ 6] = mtx[10]*sinrad + mtx06*cosrad;
	mtx[10] = mtx[10]*cosrad - mtx06*sinrad;
	
	mtx[ 7] = mtx[11]*sinrad + mtx07*cosrad;
	mtx[11] = mtx[11]*cosrad - mtx07*sinrad;
}


void RotateY(float* mtx, float deg)
{
	// [ 0 4  8 12 ]   [ cos 0  -sin 0 ]
	// [ 1 5  9 13 ] x [ 0   1  0    0 ]
	// [ 2 6 10 14 ]   [ sin 0  cos  0 ]
	// [ 3 7 11 15 ]   [ 0   0  0    1 ]
	
	float rad = deg * (M_PI/180.0f);
	
	float cosrad = cosf(rad);
	float sinrad = sinf(rad);
	
	float mtx00 = mtx[0];
	float mtx01 = mtx[1];
	float mtx02 = mtx[2];
	float mtx03 = mtx[3];
	
	mtx[ 0] = mtx[ 8]*sinrad + mtx00*cosrad;
	mtx[ 8] = mtx[ 8]*cosrad - mtx00*sinrad;
	
	mtx[ 1] = mtx[ 9]*sinrad + mtx01*cosrad;
	mtx[ 9] = mtx[ 9]*cosrad - mtx01*sinrad;
	
	mtx[ 2] = mtx[10]*sinrad + mtx02*cosrad;
	mtx[10] = mtx[10]*cosrad - mtx02*sinrad;
	
	mtx[ 3] = mtx[11]*sinrad + mtx03*cosrad;
	mtx[11] = mtx[11]*cosrad - mtx03*sinrad;
}


void RotateZ(float* mtx, float deg)
{
	// [ 0 4  8 12 ]   [ cos -sin 0  0 ]
	// [ 1 5  9 13 ] x [ sin cos  0  0 ]
	// [ 2 6 10 14 ]   [ 0   0    1  0 ]
	// [ 3 7 11 15 ]   [ 0   0    0  1 ]
	
	float rad = deg * (M_PI/180.0f);
	
	float cosrad = cosf(rad);
	float sinrad = sinf(rad);
	
	float mtx00 = mtx[0];
	float mtx01 = mtx[1];
	float mtx02 = mtx[2];
	float mtx03 = mtx[3];
	
	mtx[ 0] = mtx[ 4]*sinrad + mtx00*cosrad;
	mtx[ 4] = mtx[ 4]*cosrad - mtx00*sinrad;
	
	mtx[ 1] = mtx[ 5]*sinrad + mtx01*cosrad;
	mtx[ 5] = mtx[ 5]*cosrad - mtx01*sinrad;
	
	mtx[ 2] = mtx[ 6]*sinrad + mtx02*cosrad;
	mtx[ 6] = mtx[ 6]*cosrad - mtx02*sinrad;
	
	mtx[ 3] = mtx[ 7]*sinrad + mtx03*cosrad;
	mtx[ 7] = mtx[ 7]*cosrad - mtx03*sinrad;
}



void Rotate(float* mtx, float xAxis, float yAxis, float zAxis, float deg)
{	
	if(yAxis == 0.0f && zAxis == 0.0f)
	{
		RotateX(mtx, deg);
	}
	else if(xAxis == 0.0f && zAxis == 0.0f)
	{
		RotateY(mtx, deg);
	}
	else if(xAxis == 0.0f && yAxis == 0.0f)
	{
		RotateZ(mtx, deg);
	}
	else
	{
		float rad = deg * M_PI/180.0f;
		
		float sin_a = sinf(rad);
		float cos_a = cosf(rad);
		
		// Calculate coeffs.  No need to check for zero magnitude because we wouldn't be here.
		float magnitude = sqrtf(xAxis * xAxis + yAxis * yAxis + zAxis * zAxis);
		
		float p = 1.0f / magnitude;
		float cos_am = 1.0f - cos_a;
		
		float xp = xAxis * p;
		float yp = yAxis * p;
		float zp = zAxis * p;
		
		float xx = xp * xp;
		float yy = yp * yp;
		float zz = zp * zp;
		
		float xy = xp * yp * cos_am;
		float yz = yp * zp * cos_am;
		float zx = zp * xp * cos_am;
		
		xp *= sin_a;
		yp *= sin_a;
		zp *= sin_a;
		
		// Load coefs
		float m0  = xx + cos_a * (1.0f - xx);
		float m1  = xy + zp;
		float m2  = zx - yp;
		float m4  = xy - zp;
		float m5  = yy + cos_a * (1.0f - yy);
		float m6  = yz + xp;
		float m8  = zx + yp;
		float m9  = yz - xp;
		float m10 = zz + cos_a * (1.0f - zz);
		
		// Apply rotation 
		float c1 = mtx[0];
		float c2 = mtx[4];
		float c3 = mtx[8];
		mtx[0]  = c1 * m0 + c2 * m1 + c3 * m2;
		mtx[4]  = c1 * m4 + c2 * m5 + c3 * m6;
		mtx[8]  = c1 * m8 + c2 * m9 + c3 * m10;
		
		c1 = mtx[1];
		c2 = mtx[5];
		c3 = mtx[9];
		mtx[1]  = c1 * m0 + c2 * m1 + c3 * m2;
		mtx[5]  = c1 * m4 + c2 * m5 + c3 * m6;
		mtx[9]  = c1 * m8 + c2 * m9 + c3 * m10;
		
		c1 = mtx[2];
		c2 = mtx[6];
		c3 = mtx[10];
		mtx[2]  = c1 * m0 + c2 * m1 + c3 * m2;
		mtx[6]  = c1 * m4 + c2 * m5 + c3 * m6;
		mtx[10] = c1 * m8 + c2 * m9 + c3 * m10;
		
		c1 = mtx[3];
		c2 = mtx[7];
		c3 = mtx[11];
		mtx[3]  = c1 * m0 + c2 * m1 + c3 * m2;
		mtx[7]  = c1 * m4 + c2 * m5 + c3 * m6;
		mtx[11] = c1 * m8 + c2 * m9 + c3 * m10;
	}	
}
//=================================================================================================================================
void Translate(float* mtx, float xTrans, float yTrans, float zTrans)
{
	// [ 0 4  8 12 ]   [ 1 0 0 x ]
	// [ 1 5  9 13 ] x [ 0 1 0 y ]
	// [ 2 6 10 14 ]   [ 0 0 1 z ]
	// [ 3 7 11 15 ]   [ 0 0 0 1 ]
	
	mtx[12] += mtx[0]*xTrans + mtx[4]*yTrans + mtx[ 8]*zTrans;
	mtx[13] += mtx[1]*xTrans + mtx[5]*yTrans + mtx[ 9]*zTrans;
	mtx[14] += mtx[2]*xTrans + mtx[6]*yTrans + mtx[10]*zTrans;	
}


//=================================================================================================================================

/* Invert a row-major (C-style) 4x4 matrix. */
static void InvertMatrix(float *out, const float *m)
{
    /* Assumes matrices are ROW major. */
#define SWAP_ROWS(a, b) { double *_tmp = a; (a)=(b); (b)=_tmp; }
#define MAT(m,r,c) (m)[(r)*4+(c)]
    
    double wtmp[4][8];
    double m0, m1, m2, m3, s;
    double *r0, *r1, *r2, *r3;
    
    r0 = wtmp[0], r1 = wtmp[1], r2 = wtmp[2], r3 = wtmp[3];
    
    r0[0] = MAT(m,0,0), r0[1] = MAT(m,0,1),
    r0[2] = MAT(m,0,2), r0[3] = MAT(m,0,3),
    r0[4] = 1.0, r0[5] = r0[6] = r0[7] = 0.0,
    
    r1[0] = MAT(m,1,0), r1[1] = MAT(m,1,1),
    r1[2] = MAT(m,1,2), r1[3] = MAT(m,1,3),
    r1[5] = 1.0, r1[4] = r1[6] = r1[7] = 0.0,
    
    r2[0] = MAT(m,2,0), r2[1] = MAT(m,2,1),
    r2[2] = MAT(m,2,2), r2[3] = MAT(m,2,3),
    r2[6] = 1.0, r2[4] = r2[5] = r2[7] = 0.0,
    
    r3[0] = MAT(m,3,0), r3[1] = MAT(m,3,1),
    r3[2] = MAT(m,3,2), r3[3] = MAT(m,3,3),
    r3[7] = 1.0, r3[4] = r3[5] = r3[6] = 0.0;
    
    /* Choose myPivot, or die. */
    if (fabs(r3[0])>fabs(r2[0])) SWAP_ROWS(r3, r2);
    if (fabs(r2[0])>fabs(r1[0])) SWAP_ROWS(r2, r1);
    if (fabs(r1[0])>fabs(r0[0])) SWAP_ROWS(r1, r0);
    
    
    /* Eliminate first variable. */
    m1 = r1[0]/r0[0]; m2 = r2[0]/r0[0]; m3 = r3[0]/r0[0];
    s = r0[1]; r1[1] -= m1 * s; r2[1] -= m2 * s; r3[1] -= m3 * s;
    s = r0[2]; r1[2] -= m1 * s; r2[2] -= m2 * s; r3[2] -= m3 * s;
    s = r0[3]; r1[3] -= m1 * s; r2[3] -= m2 * s; r3[3] -= m3 * s;
    s = r0[4];
    if (s != 0.0) { r1[4] -= m1 * s; r2[4] -= m2 * s; r3[4] -= m3 * s; }
    s = r0[5];
    if (s != 0.0) { r1[5] -= m1 * s; r2[5] -= m2 * s; r3[5] -= m3 * s; }
    s = r0[6];
    if (s != 0.0) { r1[6] -= m1 * s; r2[6] -= m2 * s; r3[6] -= m3 * s; }
    s = r0[7];
    if (s != 0.0) { r1[7] -= m1 * s; r2[7] -= m2 * s; r3[7] -= m3 * s; }
    
    /* Choose myPivot, or die. */
    if (fabs(r3[1])>fabs(r2[1])) SWAP_ROWS(r3, r2);
    if (fabs(r2[1])>fabs(r1[1])) SWAP_ROWS(r2, r1);
    
    
    /* Eliminate second variable. */
    m2 = r2[1]/r1[1]; m3 = r3[1]/r1[1];
    r2[2] -= m2 * r1[2]; r3[2] -= m3 * r1[2];
    r2[3] -= m2 * r1[3]; r3[3] -= m3 * r1[3];
    s = r1[4]; if (0.0 != s) { r2[4] -= m2 * s; r3[4] -= m3 * s; }
    s = r1[5]; if (0.0 != s) { r2[5] -= m2 * s; r3[5] -= m3 * s; }
    s = r1[6]; if (0.0 != s) { r2[6] -= m2 * s; r3[6] -= m3 * s; }
    s = r1[7]; if (0.0 != s) { r2[7] -= m2 * s; r3[7] -= m3 * s; }
    
    /* Choose myPivot, or die. */
    if (fabs(r3[2])>fabs(r2[2])) SWAP_ROWS(r3, r2);
    
    
    /* Eliminate third variable. */
    m3 = r3[2]/r2[2];
    r3[3] -= m3 * r2[3], r3[4] -= m3 * r2[4],
    r3[5] -= m3 * r2[5], r3[6] -= m3 * r2[6],
    r3[7] -= m3 * r2[7];
    
    
    
    s = 1.0/r3[3];              /* Now back substitute row 3. */
    r3[4] *= s; r3[5] *= s; r3[6] *= s; r3[7] *= s;
    
    m2 = r2[3];                 /* Now back substitute row 2. */
    s  = 1.0/r2[2];
    r2[4] = s * (r2[4] - r3[4] * m2), r2[5] = s * (r2[5] - r3[5] * m2),
    r2[6] = s * (r2[6] - r3[6] * m2), r2[7] = s * (r2[7] - r3[7] * m2);
    m1 = r1[3];
    r1[4] -= r3[4] * m1, r1[5] -= r3[5] * m1,
    r1[6] -= r3[6] * m1, r1[7] -= r3[7] * m1;
    m0 = r0[3];
    r0[4] -= r3[4] * m0, r0[5] -= r3[5] * m0,
    r0[6] -= r3[6] * m0, r0[7] -= r3[7] * m0;
    
    m1 = r1[2];                 /* Now back substitute row 1. */
    s  = 1.0/r1[1];
    r1[4] = s * (r1[4] - r2[4] * m1), r1[5] = s * (r1[5] - r2[5] * m1),
    r1[6] = s * (r1[6] - r2[6] * m1), r1[7] = s * (r1[7] - r2[7] * m1);
    m0 = r0[2];
    r0[4] -= r2[4] * m0, r0[5] -= r2[5] * m0,
    r0[6] -= r2[6] * m0, r0[7] -= r2[7] * m0;
    
    m0 = r0[1];                 /* Now back substitute row 0. */
    s  = 1.0/r0[0];
    r0[4] = s * (r0[4] - r1[4] * m0), r0[5] = s * (r0[5] - r1[5] * m0),
    r0[6] = s * (r0[6] - r1[6] * m0), r0[7] = s * (r0[7] - r1[7] * m0);
    
    MAT(out,0,0) = r0[4]; MAT(out,0,1) = r0[5],
    MAT(out,0,2) = r0[6]; MAT(out,0,3) = r0[7],
    MAT(out,1,0) = r1[4]; MAT(out,1,1) = r1[5],
    MAT(out,1,2) = r1[6]; MAT(out,1,3) = r1[7],
    MAT(out,2,0) = r2[4]; MAT(out,2,1) = r2[5],
    MAT(out,2,2) = r2[6]; MAT(out,2,3) = r2[7],
    MAT(out,3,0) = r3[4]; MAT(out,3,1) = r3[5],
    MAT(out,3,2) = r3[6]; MAT(out,3,3) = r3[7]; 
    
#undef MAT
#undef SWAP_ROWS
}

//-------------------------------------------------------------------------------------------------------------------
inline void gluPerspective(float* mtx, float fovy, float aspect, float zNear, float zFar)
{
    float f  = (float)(1.0 / tan(fovy* 3.14159 / 90.0));	
	
    mtx[0]= f/aspect;	mtx[4]= 0;	mtx[ 8]= 0;								mtx[12]= 0;
	mtx[1]= 0; 		    mtx[5]= f;	mtx[ 9]= 0;								mtx[13]= 0;
	mtx[2]= 0;			mtx[6]= 0;	mtx[10]=(zFar+zNear)/(zNear-zFar) ;		mtx[14]= 2*(zFar*zNear)/(zNear-zFar);
	mtx[3]= 0;			mtx[7]=0;	mtx[11]=-1;								mtx[15]= 0;
}
//-------------------------------------------------------------------------------------------------------------------

void vectorCrossProduct(float* v1, float* v2, float*  cross ) 
{
	cross[ 0 ] = v1[ 1 ] * v2[ 2 ] - v1[ 2 ] * v2[ 1 ];		// X
	cross[ 1 ] = v1[ 2 ] * v2[ 0 ] - v1[ 0 ] * v2[ 2 ];		// Y
	cross[ 2 ] = v1[ 0 ] * v2[ 1 ] - v1[ 1 ] * v2[ 0 ];		// Z
}
//-------------------------------------------------------------------------------------------------------------------


void normalize(float* v)
{
	float length, ilength;
	
	length = (float)sqrt( v[ 0 ] * v[ 0 ] + v[ 1 ] * v[ 1 ] + v[ 2 ] * v[ 2 ] );

	if( length )
	{
		ilength = 1 / length;
		v[ 0 ] *= ilength;
		v[ 1 ] *= ilength;
		v[ 2 ] *= ilength;
	}
}
//-------------------------------------------------------------------------------------------------------------------

#define vectorClear( a )		( (a)[ 0 ] = (a)[ 1 ] = (a)[ 2 ] = 0 )
#define vectorNegate( a, b )	( (b)[ 0 ] = -(a)[ 0 ], (b)[ 1 ] = -(a)[ 1 ], (b)[ 2 ] = -(a)[ 2 ] )
#define vectorSet( v, x, y, z )	( (v)[ 0 ] = ( x ), (v)[ 1 ] = ( y ), (v)[ 2 ] = ( z ) )
#define vectorInverse( a )		( (a)[ 0 ] = (-a)[ 0 ], (a)[ 1 ] = (-a)[ 1 ], (a)[ 2 ] = (-a)[ 2 ] )

#define DotProduct( x, y )			( (x)[ 0 ] * (y)[ 0 ] + (x)[ 1 ] * (y)[ 1 ] + (x)[ 2 ] * (y)[ 2 ] )
#define vectorSubtract( a, b, c )	( (c)[ 0 ] = (a)[ 0 ] - (b)[ 0 ], (c)[ 1 ] = (a)[ 1 ] - (b)[ 1 ], (c)[ 2 ] = (a)[ 2 ] - (b)[ 2 ] )
#define vector2Subtract( a, b, c )	( (c)[ 0 ] = (a)[ 0 ] - (b)[ 0 ], (c)[ 1 ] = (a)[ 1 ] - (b)[ 1 ])
#define vectorAdd( a, b, c )		( (c)[ 0 ] = (a)[ 0 ] + (b)[ 0 ], (c)[ 1 ] = (a)[ 1 ] + (b)[ 1 ], (c)[ 2 ] = (a)[ 2 ] + (b)[ 2 ] )
#define vectorCopy( a, b )			( (b)[ 0 ] = (a)[ 0 ], (b)[ 1 ] = (a)[ 1 ], (b)[ 2 ] = (a)[ 2 ] )
#define vector2Copy( a, b )			( (b)[ 0 ] = (a)[ 0 ], (b)[ 1 ] = (a)[ 1 ] )
#define	vectorScale( v, s, o )		( (o)[ 0 ] = (v)[ 0 ] * (s),(o)[ 1 ] = (v)[ 1 ] * (s), (o)[ 2 ] = (v)[ 2 ] * (s) )
#define	vectorMA( v, s, b, o )		( (o)[ 0 ] = (v)[ 0 ] + (b)[ 0 ]*(s),(o)[ 1 ] = (v)[ 1 ] + (b)[ 1 ] * (s),(o)[ 2 ] = (v)[ 2 ] + (b)[ 2 ] * (s) )

inline  void gluLookAt(float* fModelView, float vEyeX, float vEyeY, float vEyeZ , float vLookatX, float vLookatY, float vLookatZ, float vUpX, float vUpY, float vUpZ)
{
	float vN[3]; 
    float vU[3];
    float vV[3];
	
float vEye[] = {vEyeX, vEyeY, vEyeZ}; 	
float vLookat[] = {vLookatX, vLookatY, vLookatZ}; 	
float vUp[] = {vUpX, vUpY, vUpZ}; 


vN[ 0 ] = vEye[ 0 ] - vLookat[ 0 ]; 
vN[ 1 ] = vEye[ 1 ] - vLookat[ 1 ]; 
vN[ 2 ] = vEye[ 2 ] - vLookat[ 2 ];	
    
    // determine the new u by crossing with the up vector
    //vectorCrossProduct(vUp, vN, vU) ;


	vU[ 0 ] = vUp[ 1 ] * vN[ 2 ] - vUp[ 2 ] * vN[ 1 ];		// X
	vU[ 1 ] = vUp[ 2 ] * vN[ 0 ] - vUp[ 0 ] * vN[ 2 ];		// Y
	vU[ 2 ] = vUp[ 0 ] * vN[ 1 ] - vUp[ 1 ] * vN[ 0 ];		// Z

	
 
 	float length, ilength;
	
	length = (float)sqrt( vU[ 0 ] * vU[ 0 ] + vU[ 1 ] * vU[ 1 ] + vU[ 2 ] * vU[ 2 ] );

	if( length )
	{
		ilength = 1 / length;
		vU[ 0 ] *= ilength;
		vU[ 1 ] *= ilength;
		vU[ 2 ] *= ilength;
	}   
    //-----------------------------------------------------------------------------------
	length = (float)sqrt( vN[ 0 ] * vN[ 0 ] + vN[ 1 ] * vN[ 1 ] + vN[ 2 ] * vN[ 2 ] );

	if( length )
	{
		ilength = 1 / length;
		vN[ 0 ] *= ilength;
		vN[ 1 ] *= ilength;
		vN[ 2 ] *= ilength;
	}     

 	vV[ 0 ] = vN[ 1 ] * vU[ 2 ] - vN[ 2 ] * vU[ 1 ];	
	vV[ 1 ] = vN[ 2 ] * vU[ 0 ] - vN[ 0 ] * vU[ 2 ];	
	vV[ 2 ] = vN[ 0 ] * vU[ 1 ] - vN[ 1 ] * vU[ 0 ];	
    
    
    	
    // create a model view matrix
	fModelView[0] = vU[0];					fModelView[4] = vU[1];					fModelView[8] = vU[2];					fModelView[12] = - DotProduct(vEye,vU); 
	fModelView[1] = vV[0];					fModelView[5] = vV[1];					fModelView[9] = vV[2];					fModelView[13] = - DotProduct(vEye,vV);
	fModelView[2] = vN[0];					fModelView[6] = vN[1];					fModelView[10]= vN[2];					fModelView[14]=  - DotProduct(vEye,vN);
	fModelView[3]=	0.0f;					fModelView[7]= 0.0f;					fModelView[11]= 0.0f;					fModelView[15]= 1.0f;
}
//-------------------------------------------------------------------------------------------------------------------

