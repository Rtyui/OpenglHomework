//-------------------------------------------------------------------------------------------------
// Descriere: fisier main
//
// Autor: student
// Data: today
//-------------------------------------------------------------------------------------------------

//librarie matematica 
#include "..\\dependente\glew\glew.h"
#include "..\\dependente\glm\glm.hpp"
#include "..\\dependente\glm\gtc\type_ptr.hpp"
#include "..\\dependente\glm\gtc\matrix_transform.hpp"

//neimportant pentru acest laborator, va fi explicat in viitor
#include "..\\lab_blackbox.hpp"

//interfata cu glut, ne ofera fereastra, input, context opengl
#include "..\\lab_glut.hpp"
#include "Scene.h"

//time
#include <ctime>

#include <iostream>

//clasa lab, mosteneste din WindowListener
class Lab : public lab::glut::WindowListener{

//variabile
private:

	lab::BlackBox BLACKBOX;

	unsigned int width, height;

	Scene*	scene;
	
	
//metode ale clasei lab
public:
	
	//constructor .. e apelat cand e instantiata clasa
	Lab(){
		width = lab::glut::getInitialWindowInformation().width;
		height = lab::glut::getInitialWindowInformation().height;

		scene = new Scene(&BLACKBOX);

		glutReshapeWindow(scene->GetWidth() + 8, scene->GetHeight() + 8);
	}

	//destructor .. e apelat cand e distrusa clasa
	~Lab(){
		delete scene;
	}

	//--------------------------------------------------------------------------------------------
	//functii de cadru, apelate per FIECARE cadru ------------------------------------------------
	//--------------------------------------------------------------------------------------------
	//functie chemata inainte de a incepe cadrul de desenare, o folosim ca sa updatam situatia scenei ( modelam/simulam scena)
	void notifyBeginFrame(){}
	//functia de afisare
	void notifyDisplayFrame(){
		//per ECRAN
		//bufferele din framebuffer sunt aduse la valorile initiale (setate de clear color)
		//adica se sterge ecranul si se pune culoarea initiala (si alte propietati)
		glClearColor(1, 1, 1, 0);			//la ce culoare sterg
		glClear(GL_COLOR_BUFFER_BIT);		//comanda de stergere
		BLACKBOX.notifyDisplay();

		//setez spatiul de desenare relativ la spatiul ecranului
		width = lab::glut::getInitialWindowInformation().width;
		height = lab::glut::getInitialWindowInformation().height;

		scene->Update();
		scene->Draw();

	}
	//functie chemata dupa ce am terminat cadrul de desenare (poate fi folosita pt modelare/simulare)
	void notifyEndFrame(){}
	//functie care e chemata cand se schimba dimensiunea ferestrei initiale
	void notifyReshape(int width, int height, int previos_width, int previous_height){
		//blackbox needs to know
		BLACKBOX.notifyReshape(width,height);
	}


	
	//--------------------------------------------------------------------------------------------
	//functii de input output --------------------------------------------------------------------
	//--------------------------------------------------------------------------------------------
	//tasta apasata
	void notifyKeyPressed(unsigned char key_pressed, int mouse_x, int mouse_y){
		if (key_pressed == 's')
		{
			scene->Start();
		}
		else if (key_pressed == 'l')
		{
			scene->LowerAngle();
		}
		else if (key_pressed == 'r')
		{
			scene->RaiseAngle();
		}
		else if (key_pressed == 'c')
		{
			scene->ClearRay();
		}
		else if (key_pressed == 'h')
		{
			scene->ShuffleShapes();
		}
		else if (key_pressed == 'm')
		{
			scene->SetMaxReflectionsNumber(scene->GetMaxReflectionsNumber() - 1);
		}
		else if (key_pressed == 'M')
		{
			scene->SetMaxReflectionsNumber(scene->GetMaxReflectionsNumber() + 1);

		}
		else if (key_pressed >= '1' && key_pressed <= '4')
		{
			scene->SetSpeedUp(key_pressed - 48);
		}
	}
	//tasta ridicata
	void notifyKeyReleased(unsigned char key_released, int mouse_x, int mouse_y){	}
	//tasta speciala (up/down/F1/F2..) apasata
	void notifySpecialKeyPressed(int key_pressed, int mouse_x, int mouse_y){
		if(key_pressed == GLUT_KEY_F1) lab::glut::enterFullscreen();
		if(key_pressed == GLUT_KEY_F2) lab::glut::exitFullscreen();
		
	}
	//tasta speciala ridicata
	void notifySpecialKeyReleased(int key_released, int mouse_x, int mouse_y){}
	//drag cu mouse-ul
	void notifyMouseDrag(int mouse_x, int mouse_y){ }
	//am miscat mouseul (fara sa apas vreun buton)
	void notifyMouseMove(int mouse_x, int mouse_y){ }
	//am apasat pe un boton
	void notifyMouseClick(int button, int state, int mouse_x, int mouse_y){ }
	//scroll cu mouse-ul
	void notifyMouseScroll(int wheel, int direction, int mouse_x, int mouse_y){ std::cout<<"Mouse scroll"<<std::endl;
	}

};

int main(){
	//initializeaza GLUT (fereastra + input + context OpenGL)
	lab::glut::WindowInfo window(std::string("Lab EGC 3 - transformari"),1000,600,300,50,true);
	lab::glut::ContextInfo context(3,3,false);
	lab::glut::FramebufferInfo framebuffer(true,true,false,false);
	lab::glut::init(window, context, framebuffer);

	//initializeaza GLEW (ne incarca functiile openGL, altfel ar trebui sa facem asta manual!)
	glewExperimental = true;
	glewInit();
	std::cout<<"GLEW:initializare"<<std::endl;

	//creem clasa noastra si o punem sa asculte evenimentele de la GLUT
	//_DUPA_ GLEW ca sa avem functiile de OpenGL incarcate inainte sa ii fie apelat constructorul (care creeaza obiecte OpenGL)
	Lab mylab;
	lab::glut::setListener(&mylab);

	//run
	lab::glut::run();

	return 0;
}