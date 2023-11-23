//
// Created by jakit on 2023/11/22.
//

const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 "}\0";

//const char *fragmentShaderSource = "#version 330 core\n"
//                                   "out vec4 FragColor;\n"
//                                   "void main()\n"
//                                   "{\n"
//                                   "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
//                                   "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "uniform vec4 color;\n"
                                   "void main()\n"
                                   "{\n"
                                   "   FragColor = color;\n"
                                   "}\0";

struct Vector2 {
    float x;
    float y;
};

struct Vector3 {
    float x;
    float y;
    float z;
};

struct Vector4 {
    float x;
    float y;
    float z;
    float w;
};

struct Shape {
    Choco::UInt32 va;
    Choco::UInt32 vb;
    std::vector<Vector3> points;
    Choco::UInt32 mode;
    Vector4 color;

    Shape(Choco::UInt32 mode = 0) : va(0), vb(0), mode(mode) {
        // Create Vertex Array
        glad::glGenVertexArrays(1, &va);

        // Create Vertex Buffer
        glad::glGenBuffers(1, &vb);

        // Bind them VBO -> VAO
        glad::glBindVertexArray(va);
        glad::glBindBuffer(GL_ARRAY_BUFFER, vb);

        color = Vector4{1.0f, 1.0f, 1.0f, 1.0f};
    }

    void push(const Vector3 & point) {
        points.push_back(point);
    }

    void setColor(float r, float g, float b, float a) {
        color.x = r;
        color.y = g;
        color.z = b;
        color.w = a;
    }

    static Shape * CreateTriangle(float x1, float y1, float z1,
                                  float x2, float y2, float z2,
                                  float x3, float y3, float z3) {
        auto shape = new Shape(GL_TRIANGLES);

        Vector3 point1{x1, y1, z1}, point2{x2, y2, z2}, point3{x3, y3, z3};
        shape->push(point1);
        shape->push(point2);
        shape->push(point3);

        // Create a BufferData for VBO which you bind before
        glad::glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 9,
                           reinterpret_cast<void *>(&shape->points[0]), GL_STATIC_DRAW);

        // Tell video card how to analyse the value of them
        glad::glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, nullptr);
        // Enable the first value of VAO
        glad::glEnableVertexAttribArray(0);

        // Clean up
        glad::glBindBuffer(GL_ARRAY_BUFFER, 0);
        glad::glBindVertexArray(0);

        return shape;
    }

    static Shape * CreateLine(float x1, float y1, float z1,
                              float x2, float y2, float z2) {
        auto shape = new Shape(GL_LINES);

        Vector3 point1{x1, y1, z1}, point2{x2, y2, z2};
        shape->push(point1);
        shape->push(point2);

        // Create a BufferData for VBO which you bind before
        glad::glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6,
                           reinterpret_cast<void *>(&shape->points[0]), GL_STATIC_DRAW);

        // Tell video card how to analyse the value of them
        glad::glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, nullptr);
        // Enable the first value of VAO
        glad::glEnableVertexAttribArray(0);

        // Clean up
        glad::glBindBuffer(GL_ARRAY_BUFFER, 0);
        glad::glBindVertexArray(0);

        return shape;
    }
};

float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
};

float vertices1[] = {
        -0.5f, -0.5f, 0.0f,
        -0.5f, 0.5, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.5f, 0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f
};

Choco::UInt32 CompileShader(Choco::UInt32 type, const char * source) {
    std::cout << source << std::endl;
    Choco::UInt32 shader = glad::glCreateShader(type);
    glad::glShaderSource(shader, 1, &source, nullptr);
    glad::glCompileShader(shader);

    int result;
    glad::glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length = 0;
        glad::glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

        if (length > 0) {
            char * message = new char[length + 1];
            Choco::Fill(reinterpret_cast<Choco::Byte *>(message), length + 1, 0);
            glad::glGetShaderInfoLog(shader, length, &length, message);
            std::cout << "Compile failed type[" << type << "]: ";
            std::cout << message << std::endl;
            glad::glDeleteShader(shader);
            delete [] message;
        }
        return 0;
    }

    return shader;
}

Choco::UInt32 CreateProgram(const char * vertexShaderSource, const char * fragmentShaderSource) {
    Choco::UInt32 vertexShader = CompileShader(GL_VERTEX_SHADER, vertexShaderSource);
    Choco::UInt32 fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    if (vertexShader == 0 || fragmentShader == 0) {
        return 0;
    }

    Choco::UInt32 program = glad::glCreateProgram();
    // Attach them to program
    glad::glAttachShader(program, vertexShader);
    glad::glAttachShader(program, fragmentShader);
    // Link to video card
    glad::glLinkProgram(program);

    glad::glDeleteShader(vertexShader);
    glad::glDeleteShader(fragmentShader);

    return program;
}

void test_main() {
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(800, 600, "Hello World", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (!glad::gladLoadGLLoader(reinterpret_cast<glad::LOADER>(glfwGetProcAddress))) {
        std::cout << "ERROR" << std::endl;
        glfwTerminate();
        return -1;
    }

    auto triangle = Shape::CreateTriangle(-0.5f, -0.5f, 0.0f,
                                          0.5f, -0.5f, 0.0f,
                                          0.0f,  0.5f, 0.0f);
    triangle->color.y = 0.0f;
    triangle->color.z = 0.0f;

    auto line = Shape::CreateLine(-0.5f, 0.5f, 0.0f,
                                  0.5f, 0.5f, 0.0f);
    line->color.x = 0.0f;
    line->color.z = 0.0f;

    Choco::UInt32 program = CreateProgram(vertexShaderSource, fragmentShaderSource);

    int color = glad::glGetUniformLocation(program, "color");

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /*your draw*/
//        drawLine();
        // drawLint();
//        drawTriangle();

        glad::glClearColor(0.2, 0.3, 0.3, 1);
        glad::glClear(GL_COLOR_BUFFER_BIT);

        glad::glUseProgram(program);

//        glad::glBindVertexArray(VAO);
//        glad::glDrawArrays(GL_TRIANGLES, 0, 6);

        glad::glUniform4f(color, triangle->color.x, triangle->color.y,
                          triangle->color.z, triangle->color.w);
        glad::glBindVertexArray(triangle->va);
        glad::glDrawArrays(triangle->mode, 0, 3);

        glad::glUniform4f(color, line->color.x, line->color.y,
                          line->color.z, line->color.w);
        glad::glBindVertexArray(line->va);
        glad::glDrawArrays(line->mode, 0, 2);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glad::glDeleteProgram(program);
    delete triangle;

    glfwTerminate();
}