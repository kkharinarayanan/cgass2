
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

extern double poly_d;


typedef struct Vertex {
  float x, y, z;
} Vertex;

typedef struct Face {

  int nverts;
  Vertex **verts;
  float normal[3];
} Face;

typedef struct Mesh {

  int nverts;
  Vertex *verts;
  int nfaces;
  Face *faces;
  
  GLfloat *vertx;
  GLfloat *norms;
  GLubyte *indx;
  int indx_cnt;
 
} Mesh;



Mesh *
ReadOffFile(const char *filename)
{
  int i;
  
  int *vt,*normcnt;
  


  FILE *fp;
  if (!(fp = fopen(filename, "r"))) {
    fprintf(stderr, "Unable to open file %s\n", filename);
    return 0;
  }

  Mesh *mesh = new Mesh();
  if (!mesh) {
    fprintf(stderr, "Unable to allocate memory for file %s\n", filename);
    fclose(fp);
    return 0;
  }
  mesh->indx_cnt = 0;

  int nverts = 0;
  int nfaces = 0;
  int nedges = 0;
  int line_count = 0;
  char buffer[1024];
  while (fgets(buffer, 1023, fp)) {
    line_count++;

    char *bufferp = buffer;
    while (isspace(*bufferp)) bufferp++;

    if (*bufferp == '#') continue;
    if (*bufferp == '\0') continue;

    if (nverts == 0) {
      if (!strstr(bufferp, "OFF")) {
        if ((sscanf(bufferp, "%d%d%d", &nverts, &nfaces, &nedges) != 3) || (nverts == 0)) {
          fprintf(stderr, "Syntax error reading header on line %d in file %s\n", line_count, filename);
          fclose(fp);
          return NULL;
        }

        mesh->verts = new Vertex [nverts];
        assert(mesh->verts);
        mesh->faces = new Face [nfaces];
        assert(mesh->faces);
        
        normcnt = (int*)malloc(sizeof(int)*nverts);
        mesh->norms = (float*)malloc(sizeof(float)*nverts*3);
        mesh->indx = (GLubyte *)malloc(sizeof(GLubyte)*nfaces*3);
        mesh->vertx = (GLfloat*)malloc(sizeof(GLfloat)*nverts*3);
      }
    }
    else if (mesh->nverts < nverts) {

      Vertex& vert = mesh->verts[mesh->nverts++];
      if (sscanf(bufferp, "%f%f%f", &(vert.x), &(vert.y), &(vert.z)) != 3) {
        fprintf(stderr, "Syntax error with vertex coordinates on line %d in file %s\n", line_count, filename);
        fclose(fp);
        return NULL;
      }
      mesh->vertx[3*mesh->nverts-3] = (GLfloat)vert.x;
      mesh->vertx[3*mesh->nverts-2] =(GLfloat)vert.y;
      mesh->vertx[3*mesh->nverts] = (GLfloat)vert.z;
      
    }
    else if (mesh->nfaces < nfaces) {

      Face& face = mesh->faces[mesh->nfaces++];

      bufferp = strtok(bufferp, " \t");
      if (bufferp) face.nverts = atoi(bufferp);
      else {
        fprintf(stderr, "Syntax error with face on line %d in file %s\n", line_count, filename);
        fclose(fp);
        return NULL;
      }

      // Allocate memory for face vertices
      face.verts = new Vertex *[face.nverts];
      assert(face.verts);

      // Read vertex indices for face
      vt =  (int*)malloc(sizeof(int)*face.nverts);
      
      for (i = 0; i < face.nverts; i++) {
        bufferp = strtok(NULL, " \t");
        if (bufferp) {
        face.verts[i] = &(mesh->verts[atoi(bufferp)]);
        
        vt[i] = atoi(bufferp);
        mesh->indx[3*mesh->nfaces+i] = (GLubyte)atoi(bufferp);
        mesh->indx_cnt++;
        }
        
        else {
          fprintf(stderr, "Syntax error with face on line %d in file %s\n", line_count, filename);
          fclose(fp);
          return NULL;
        }
      }

      face.normal[0] = face.normal[1] = face.normal[2] = 0;
      Vertex *v1 = face.verts[face.nverts-1];
      for (i = 0; i < face.nverts; i++) {
        Vertex *v2 = face.verts[i];
        face.normal[0] += (v1->y - v2->y) * (v1->z + v2->z);
        face.normal[1] += (v1->z - v2->z) * (v1->x + v2->x);
        face.normal[2] += (v1->x - v2->x) * (v1->y + v2->y);
        v1 = v2;
      }

      float squared_normal_length = 0.0;
      squared_normal_length += face.normal[0]*face.normal[0];
      squared_normal_length += face.normal[1]*face.normal[1];
      squared_normal_length += face.normal[2]*face.normal[2];
      float normal_length = sqrt(squared_normal_length);
      if (normal_length > 1.0E-6) {
      
        face.normal[0] /= normal_length;
        face.normal[1] /= normal_length;
        face.normal[2] /= normal_length;
        
        for(int k=0;k<face.nverts;k++){
        
        mesh->norms[3*vt[k]  ] +=  face.normal[0];
        mesh->norms[3*vt[k]+1] +=  face.normal[1];
        mesh->norms[3*vt[k]+2] +=  face.normal[2];
        
        normcnt[vt[k]]++;  
        
        }
      }
      
      free(vt);
    }
    else {

      fprintf(stderr, "Found extra text starting at line %d in file %s\n", line_count, filename);
      break;
    }
  }


  if (nfaces != mesh->nfaces) {
    fprintf(stderr, "Expected %d faces, but read only %d faces in file %s\n", nfaces, mesh->nfaces, filename);
  }


  fclose(fp);
  //free(normcnt);

  return mesh;
 
}






double mesh_gen(Mesh *mesh,float scale,float xtrans,float ytrans, float ztrans,double theta){



  int i;
  double height=0;
  scale  *= 2;
  
  double miny=10000;
  double maxx=0,minx=100000,minz=10000,maxz=0;
  
  glPushMatrix();
  glTranslatef(xtrans,ytrans,ztrans);
  glRotatef(theta, 0, 1, 0);
     
	//glVertexPointer(3,GL_FLOAT,0,mesh->vertx);
	//glNormalPointer(GL_FLOAT,0,mesh->norms);	    
	     
	//glDrawElements(GL_TRIANGLES,mesh->indx_cnt,
	//	GL_UNSIGNED_BYTE,mesh->indx);
  
 glPopMatrix();
 return(1);
 }


