aieutilities
============

Additional code utilities that can be added to your project.

These classes and files are meant to assist with your ability to create real-time applications, but not to be a crutch to rely on all the time. You should use them as references for creating your own implementations.

<b>Gizmos</b>
- The Gizmos class implements simple geometric immediate-mode rendering in OpenGL. It is self contained and implements its own shaders and states. At the beginning of each frame you should clear the gizmos, then add any shapes you want draw. Then when you call the Gizmos::draw() methods they will display whatever was added since the last call to Gizmos::clear().
```c++
  // clear the gizmos out for this frame
  Gizmos::clear();

  // add a red line
  Gizmos::addLine(vec3(0), vec3(10), vec4(1, 0, 0, 1));
  // add a matrix transform (rgb lines)
  Gizmos::addTransform(mat4(1));

  // display the 3D gizmos
  Gizmos::draw(m_camera->getProjectionView());
  // display the 2D gizmos
  Gizmos::draw2D(glm::ortho<float>(0, (float)width, 0, (float)height));
```
<b>Camera</b>
- Implements a base camera class to wrap up a camera world transform matrix as well as a view matrix and projection matrix, in addition to a combined projection * view matrix.
- Also implements a derived <b>FlyCamera</b> class that uses the keybpoard WASD keys for movement, QE keys to raise / lower the camera, and the mouse movement for rotation, but only while mouse button 2 is held. Holding the SHIFT key doubles movement speed.
```c++
  // setup camera
  m_camera = new FlyCamera(glm::pi<float>() * 0.25f, 16 / 9.f, 0.1f, 1000.f);
  // look at vec3(0,0,0) from vec3(10,10,10)
  m_camera->setLookAtFrom(vec3(10), vec3(0));
  
  // update the camera's movement
  m_camera->update(deltaTime);
```
<b>Mesh</b>
- Implements an OBJ file wrapper with OpenGL buffer creation.
- Handles loading textures if desired and can flip texture coordinate if needed (OpenGL vs Direct3D).
```c++
  // load a mesh
  m_mesh = new Mesh();
  if (m_mesh->loadObj("./models/bunny.obj", true, true) == false)
    return false;
    
  // draw mesh as a triangle mesh
  m_mesh->draw(GL_TRIANGLES);
```
<b>Shader</b>
- Implements a GLSL shader wrapper class for loading and using shaders.
```c++
  // load a shader
  m_shader = new Shader();
  if (m_shader->loadShader(GL_VERTEX_SHADER, "./shaders/textured.vert") == false) {
    printf("Vertex Shader Error: %s\n", m_shader->getLastError());
    return false;
  }
  if (m_shader->loadShader(GL_FRAGMENT_SHADER, "./shaders/textured.frag") == false) {
    printf("Fragment Shader Error: %s\n", m_shader->getLastError());
    return false;
  }
  if (m_shader->link() == false) {
    printf("Shader Link Error: %s\n", m_shader->getLastError());
    return false;
  }
  
  // bind shader
  m_shader->bind();
```
