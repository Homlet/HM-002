// "Matrices.cpp"
//

#include "Base.h"
#include "Matrices.h"

using namespace render;


// --------------------------------------------------------------------------------------------------------------------
//  Loads all matrices to identity
//
Matrices::Matrices() :
	     _model( glm::mat4( 1.0 ) ),
	      _view( glm::mat4( 1.0 ) ),
	_projection( glm::mat4( 1.0 ) ),
	 _modelView( glm::mat4( 1.0 ) )
{

}


// --------------------------------------------------------------------------------------------------------------------
//  Loads the _model matrix to identity
//
void Matrices::loadIdentity( void )
{
	_model = glm::mat4( 1.0 );
}


// --------------------------------------------------------------------------------------------------------------------
//  Translates the _model matrix
//
void Matrices::translate( glm::vec3 translation )
{
	_model *= glm::translate( translation );
}


// --------------------------------------------------------------------------------------------------------------------
//  Rotates the _model matrix
//
void Matrices::rotate( glm::vec3 axis, float angle )
{
	_model *= glm::rotate( angle, axis );
}


// --------------------------------------------------------------------------------------------------------------------
//  Scales the _model matrix
//
void Matrices::scale( glm::vec3 scale )
{
	_model *= glm::scale( scale );
}


// --------------------------------------------------------------------------------------------------------------------
//  Sets the _view matrix using glm::lookAt. Use to move the camera
//
void Matrices::setView( glm::vec3 cameraPosition, glm::vec3 cameraTarget, glm::vec3 upVector)
{
	_view = glm::lookAt(
		cameraPosition,
		cameraTarget,
		upVector
	);
}


// --------------------------------------------------------------------------------------------------------------------
//  Sets the _projection matrix using glm::perspective. Use only in initialisation or to change the FoV
//
void Matrices::setProjection( float fov, float aspectRatio, float nearClip, float farClip )
{
	_projection = glm::perspective(
		fov,
		aspectRatio,
		nearClip,
		farClip
	);
}


// --------------------------------------------------------------------------------------------------------------------
//  Sets _modelView to the product of all three current matrices
//
void Matrices::computeModelView( void )
{
	_modelView = _view * _model;
}


// --------------------------------------------------------------------------------------------------------------------
//  Returns _modelView
//
glm::mat4 Matrices::getModelView( void ) const
{
	return _modelView;
}


// --------------------------------------------------------------------------------------------------------------------
//  Returns _projection
//
glm::mat4 Matrices::getProjection( void ) const
{
	return _projection;
}
