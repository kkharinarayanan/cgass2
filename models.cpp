
extern GLuint m_texname[1];

float barcolor[] = { 0.1f, 0.05f, 0.05, 1.0f };
float roadcolor[] = { 0.1f, 0.1f, 0.1f, 1.0f };
float grasscolor[] = { 0.1f, 0.3f, 0.1f, 1.0f };
float blackchaircolor[] = { 0.1f, 0.1f, 0.1f, 1.0f };
float bluechaircolor[] = { 0.0f, 0.0f, 0.1f, 1.0f };
float Treecolor[] =  { 0.1f, 0.3f, 0.1f, 1.0f };
float wallcolor[] =  { 0.3f, 0.35f, 0.3f, 1.0f };


void bar(double sy){

double sx  =0.1;
double sz = 0.1;
	GLfloat verts_t[24] = {-0.5*sx,0*sy,-0.5*sz,
				0.5*sx,0*sy,-0.5*sz,
				0.5*sx,0*sy,0.5*sz,
				-0.5*sx,0*sy,0.5*sz,
				-0.5*sx,0.5*sy,-0.5*sz,
				0.5*sx,0.5*sy,-0.5*sz,
				0.5*sx,0.5*sy,0.5*sz,
				-0.5*sx,0.5*sy,0.5*sz};
			 	
	GLfloat norms[24] = {	1,1,1,
				1,0,1,
				1,1,0,
				1,0,1,
				0,0,1,
				1,0,0,
				1,1,1,
				1,1,1};
	
	glVertexPointer(3,GL_FLOAT,0,verts_t);
	glNormalPointer(GL_FLOAT,0,norms);
		
		 	 
	GLubyte indices_t[24]  = {0,1,5,4
				,1,2,6,5
				,2,3,7,6
				,7,3,0,4
				,1,0,3,2
				,4,5,6,7}; 	

	glDrawElements(GL_QUADS,24,GL_UNSIGNED_BYTE,indices_t);

		
}

void tile_gen(double x, double z,float rail){


	rail = rail/2;
	
	glPushMatrix();
	
	glTranslatef(x,0,z);
	
	glPushMatrix();
	
	glEnable(GL_TEXTURE_2D);

         glShadeModel(GL_FLAT); 
        glBindTexture(GL_TEXTURE_2D,m_texname[0]); 
        
	glBegin(GL_QUADS);       
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, grasscolor);
	
	glNormal3f(0, 1, 0);								//making the area inside cage
	glTexCoord2f(0.0, 0.0);glVertex3f(-8,-0.01,-8);
	glTexCoord2f(0.0, 1.0);glVertex3f(-8,-0.01,8);
	glTexCoord2f(1.0, 1.0);glVertex3f(8,-0.01,8);
	glTexCoord2f(1.0, 0.0);glVertex3f(8,-0.01,-8);
	glEnd();
	
	glDisable(GL_TEXTURE_2D);
	
	glPopMatrix();
	
		
	glBegin(GL_QUADS);										//makinh the border of the cage	
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, roadcolor);
	glVertex3f(-10,-0.01,-10);	
	glVertex3f(-10,-0.01,10);		
	glVertex3f(-8,-0.01,10);
	glVertex3f(-8,-0.01,-10);

	glVertex3f(8,-0.01,-10);	
	glVertex3f(8,-0.01,10);
	glVertex3f(10,-0.01,10);
	glVertex3f(10,-0.01,-10);

	glVertex3f(-8,-0.01,-10);
	glVertex3f(-8,-0.01,-8);
	glVertex3f(8,-0.01,-8);
	glVertex3f(8,-0.01,-10);
	
	glVertex3f(-8,-0.01,8);
	glVertex3f(-8,-0.01,10);
	glVertex3f(8,-0.01,10);
	glVertex3f(8,-0.01,8);
	
	glEnd();

	
	if(rail){	
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, barcolor);
	int i,j;
	GLUquadricObj *quadric;
	quadric = gluNewQuadric();
	
	glPushMatrix();
	glTranslatef(-8,0,-8);
	for(i = 0;i<67;i++){
	
		glPushMatrix();
		glTranslatef(0,0,i/4);
		bar(6);
		glPopMatrix();
		
		glPushMatrix();
		glTranslatef(i/4,0,0);
		bar(6);
		glPopMatrix();	
				
	}
	glPopMatrix();
	
	
	glPushMatrix();
	glTranslatef(8,0,8);
	for(i = 0;i<67;i++){	
		glPushMatrix();
		glTranslatef(0,0,-i/4);
		bar(6);
		glPopMatrix();
		
		glPushMatrix();
		glTranslatef(-i/4,0,0);
		bar(6);
		glPopMatrix();	
	}
	
	//making the structurer above the rails
		
	glBegin(GL_QUADS);
	
	glNormal3f(1,0,0);
	glVertex3f(.1,3,0);
	glVertex3f(.1,4,0);		
	glVertex3f(.1,4,-16);
	glVertex3f(.1,3,-16);
		
	glNormal3f(-1,0,0);
	glVertex3f(-.1,3,0);
	glVertex3f(-.1,4,0);		//vert
	glVertex3f(-.1,4,-16);
	glVertex3f(-.1,3,-16);
		
	glNormal3f(0,-1,0);
	glVertex3f(-.1,3,0);
	glVertex3f(.1,3,0);		//vert
	glVertex3f(.1,3,-16);
	glVertex3f(-.1,3,-16);

	glNormal3f(0,0,1);
	glVertex3f(-.1,3,0);
	glVertex3f(-.1,4,0);		//vert
	glVertex3f(.1,4,0);
	glVertex3f(.1,3,0);

	glNormal3f(0,1,0);
	glVertex3f(-.1,4,0);
	glVertex3f(.1,4,0);		//vert
	glVertex3f(.1,4,-16);
	glVertex3f(-.1,4,-16);
	
	glNormal3f(0,0,1);
	glVertex3f(-.1,3,-16);
	glVertex3f(-.1,4,-16);		//vert
	glVertex3f(.1,4,-16);
	glVertex3f(.1,3,-16);
	glEnd();
	
		
	glTranslatef(-16,0,0);	
	glBegin(GL_QUADS);
		
	glNormal3f(1,0,0);
	glVertex3f(.1,3,0);
	glVertex3f(.1,4,0);		//vert
	glVertex3f(.1,4,-16);
	glVertex3f(.1,3,-16);
	
	glNormal3f(-1,0,0);
	glVertex3f(-.1,3,0);
	glVertex3f(-.1,4,0);		//vert
	glVertex3f(-.1,4,-16);
	glVertex3f(-.1,3,-16);

	glNormal3f(0,-1,0);
	glVertex3f(-.1,3,0);
	glVertex3f(.1,3,0);		//vert
	glVertex3f(.1,3,-16);
	glVertex3f(-.1,3,-16);

	glNormal3f(0,0,1);
	glVertex3f(-.1,3,0);
	glVertex3f(-.1,4,0);		//vert
	glVertex3f(.1,4,0);
	glVertex3f(.1,3,0);
	
	glNormal3f(0,1,0);
	glVertex3f(-.1,4,0);
	glVertex3f(.1,4,0);		//vert
	glVertex3f(.1,4,-16);
	glVertex3f(-.1,4,-16);
	
	glNormal3f(0,0,1);
	glVertex3f(-.1,3,-16);
	glVertex3f(-.1,4,-16);		//vert
	glVertex3f(.1,4,-16);
	glVertex3f(.1,3,-16);
	glEnd();
		
		
	glRotatef(-90,0,1,0);		
	glBegin(GL_QUADS);

	glNormal3f(1,0,0);
	glVertex3f(.1,3,0);
	glVertex3f(.1,4,0);		//vert
	glVertex3f(.1,4,-16);
	glVertex3f(.1,3,-16);
	
	glNormal3f(-1,0,0);
	glVertex3f(-.1,3,0);
	glVertex3f(-.1,4,0);		//vert
	glVertex3f(-.1,4,-16);
	glVertex3f(-.1,3,-16);

	glNormal3f(0,-1,0);
	glVertex3f(-.1,3,0);
	glVertex3f(.1,3,0);		//vert
	glVertex3f(.1,3,-16);
	glVertex3f(-.1,3,-16);

	glNormal3f(0,0,1);
	glVertex3f(-.1,3,0);
	glVertex3f(-.1,4,0);		//vert
	glVertex3f(.1,4,0);
	glVertex3f(.1,3,0);

	glNormal3f(0,1,0);
	glVertex3f(-.1,4,0);
	glVertex3f(.1,4,0);		//vert
	glVertex3f(.1,4,-16);
	glVertex3f(-.1,4,-16);
	
	glNormal3f(0,0,1);
	glVertex3f(-.1,3,-16);
	glVertex3f(-.1,4,-16);		//vert
	glVertex3f(.1,4,-16);
	glVertex3f(.1,3,-16);
	glEnd();
		
	
	glTranslatef(-16,0,0);	
	glBegin(GL_QUADS);

	glNormal3f(1,0,0);
	glVertex3f(.1,3,0);
	glVertex3f(.1,4,0);		//vert
	glVertex3f(.1,4,-16);
	glVertex3f(.1,3,-16);
	
	glNormal3f(-1,0,0);
	glVertex3f(-.1,3,0);
	glVertex3f(-.1,4,0);		//vert
	glVertex3f(-.1,4,-16);
	glVertex3f(-.1,3,-16);

	glNormal3f(0,-1,0);
	glVertex3f(-.1,3,0);
	glVertex3f(.1,3,0);		//vert
	glVertex3f(.1,3,-16);
	glVertex3f(-.1,3,-16);
	
	glNormal3f(0,0,1);
	glVertex3f(-.1,3,0);
	glVertex3f(-.1,4,0);		//vert
	glVertex3f(.1,4,0);
	glVertex3f(.1,3,0);
	
	glNormal3f(0,1,0);
	glVertex3f(-.1,4,0);
	glVertex3f(.1,4,0);		//vert
	glVertex3f(.1,4,-16);
	glVertex3f(-.1,4,-16);
		
	glNormal3f(0,0,1);
	glVertex3f(-.1,3,-16);
	glVertex3f(-.1,4,-16);		//vert
	glVertex3f(.1,4,-16);
	glVertex3f(.1,3,-16);
	glEnd();
		
	glPopMatrix();	
	}
glPopMatrix();
}

void tile_gen_free(double x, double z,Mesh* m,Mesh *Chairblack,Mesh *Chairblue,GLfloat *c,int n){

	glPushMatrix();
	glTranslatef(x,0,z);
	tile_gen(0,0,0);//not


	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, blackchaircolor);
	mesh_gen(Chairblack,0.3,-5,0,-6,0,c,n);
	mesh_gen(Chairblack,0.3,0,0,-6,0,c,n );	
	mesh_gen(Chairblack,0.3,5,0,-6,0,c,n );	
	

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, bluechaircolor);
	mesh_gen(Chairblue,.7,-6,0,-5,-90,c,n );
	mesh_gen(Chairblue,.7,-6,0,0,-90,c,n );	
	mesh_gen(Chairblue,.7,-6,0,5,-90,c,n );
	
	
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,Treecolor);
	glColor3fv(Treecolor);
	mesh_gen(m,0.05,0,0,0,0,c,n );
	
	glPopMatrix();
	
}


void make_wall(){
	
	glPushMatrix();
	
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, wallcolor);
	glBegin(GL_POLYGON);	//generating the axes
	INCPOLY;
	glNormal3f(-1, 0, 0);
	glVertex3f(14,0,13);
	glVertex3f(14,3,13);
	glVertex3f(14,3,-74);
	glVertex3f(14,0,-74);
	glEnd();
	
	glBegin(GL_POLYGON);	//generating the axes
	INCPOLY;
	glNormal3f(1, 0, 0);
	glVertex3f(14.5,0,13);
	glVertex3f(14.5,3,13);
	glVertex3f(14.5,3,-74);
	glVertex3f(14.5,0,-74);
	glEnd();
	
	
	glColor3f(0.1,.1,0.1);
	glBegin(GL_POLYGON);	//generating the axes
	INCPOLY;
	glNormal3f(1, 0, 0);
	glVertex3f(-92,0,13);
	glVertex3f(-92,3,13);
	glVertex3f(-92,3,-74);
	glVertex3f(-92,0,-74);
	glEnd();
	
	glBegin(GL_POLYGON);	//generating the axes
	INCPOLY;
	glNormal3f(-1, 0, 0);
	glVertex3f(-92.5,0,13);
	glVertex3f(-92.5,3,13);
	glVertex3f(-92.5,3,-74);
	glVertex3f(-92.5,0,-74);
	glEnd();
	
	
	glColor3f(0.1,.1,0.1);
	glBegin(GL_POLYGON);	//generating the axes
	INCPOLY;
	glNormal3f(0, 0, -1);
	glVertex3f(14.5,0,13);
	glVertex3f(14.5,3,13);
	glVertex3f(-92.5,3,13);
	glVertex3f(-92.5,0,13);
	glEnd();
	
	glColor3f(0.1,.1,0.1);
	glBegin(GL_POLYGON);	//generating the axes
	INCPOLY;
	glNormal3f(0, 0, 1);
	glVertex3f(13.5,0,13.5);
	glVertex3f(13.5,3,13.5);
	glVertex3f(-92.5,3,13.5);
	glVertex3f(-92.5,0,13.5);
	glEnd();
	
	
	glBegin(GL_POLYGON);	//generating the axes
	INCPOLY;
	glNormal3f(0, 0, 1);
	glVertex3f(14.5,0,-74);
	glVertex3f(14.5,3,-74);
	glVertex3f(-92.5,3,-74);
	glVertex3f(-92.5,0,-74);
	glEnd();
	
	glBegin(GL_POLYGON);	//generating the axes
	INCPOLY;
	glNormal3f(0, 0, -1);
	glVertex3f(14.5,0,-74.5);
	glVertex3f(14.5,3,-74.5);
	glVertex3f(-92.5,3,-74.5);
	glVertex3f(-92.5,0,-74.5);
	glEnd();
	
	
	glPopMatrix();
	}






void create_background(Mesh *Tree,Mesh *Chairblack,Mesh *Chairblue,GLfloat *c,int n)
{
	
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, grasscolor);

	glBegin(GL_POLYGON);	//generating the ground 
	glNormal3f(0, 1, 0);
	glVertex3f(-5000,-0.1,-5000);
	glVertex3f(-5000, -0.1,5000);
	glVertex3f(5000, -0.1,5000);
	glVertex3f(5000, -0.1,-5000);
	glEnd();

	make_wall();
	tile_gen_free(-10,-10,Tree,Chairblack,Chairblue,c,n);
	tile_gen(-30,-10,5);
	tile_gen(-50,-10,5);
	tile_gen_free(-70,-10,Tree,Chairblack,Chairblue,c,n);
	tile_gen(-10,-30,5);
	tile_gen(-30,-30,0);
	tile_gen_free(-50,-30,Tree,Chairblack,Chairblue,c,n);
	tile_gen(-70,-30,5);
	tile_gen_free(-10,-50,Tree,Chairblack,Chairblue,c,n);
	tile_gen(-30,-50,5);
	tile_gen(-50,-50,5);
	tile_gen_free(-70,-50,Tree,Chairblack,Chairblue,c,n);
		
}