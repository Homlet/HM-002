// "Matrices.cpp"
//

#include "Render.h"

using namespace render;


// --------------------------------------------------------------------------------------------------------------------
//  Loads all matrices to identity
//
Matrices::Matrices() :
	              model( glm::mat4( 1.0 ) ),
	               view( glm::mat4( 1.0 ) ),
	         projection( glm::mat4( 1.0 ) ),
	modelViewProjection( glm::mat4( 1.0 ) )
{

}


// --------------------------------------------------------------------------------------------------------------------
//  Loads the model matrix to identity
//
void Matrices::loadIdentity( void )
{
	model = glm::mat4( 1.0 );
}


// --------------------------------------------------------------------------------------------------------------------
//  Translates the model matrix
//
void Matrices::translate( glm::vec3 translation )
{
	model *= glm::translate( translation );
}


// --------------------------------------------------------------------------------------------------------------------
//  Rotates the model matrix
//
void Matrices::rotate( glm::vec3 axis, float angle )
{
	model *= glm::rotate( angle, axis );
}


// --------------------------------------------------------------------------------------------------------------------
//  Scales the model matrix
//
void Matrices::scale( glm::vec3 scale )
{
	model *= glm::scale( scale );
}


// --------------------------------------------------------------------------------------------------------------------
//  Sets the view matrix using glm::lookAt. Use to move the camera
//
void Matrices::setView( glm::vec3 cameraPosition, glm::vec3 cameraTarget, glm::vec3 upVector)
{
	view = glm::lookAt(
		cameraPosition,
		cameraTarget,
		upVector
	);
}


// --------------------------------------------------------------------------------------------------------------------
//  Sets the projection matrix using glm::perspective. Use only in initialisation or to change the FoV
//
void Matrices::setProjection( float fov, float aspectRatio, float nearClip, float farClip )
{
	projection = glm::perspective(
		fov,
		aspectRatio,
		nearClip,
		farClip
	);
}


// --------------------------------------------------------------------------------------------------------------------
//  Sets modelViewProjection to the product of all three current matrices
//
void Matrices::computeModelViewProjection( void )
{
	modelViewProjection = projection * view * model;
}


// --------------------------------------------------------------------------------------------------------------------
//  Returns modelViewProjection
//
glm::mat4 Matrices::getModelViewProjection( void )
{
	return modelViewProjection;
}
