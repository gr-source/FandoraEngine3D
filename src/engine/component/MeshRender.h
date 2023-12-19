#include "../Global.h"
#include "../Material.h"

class MeshRender : public Component {
private:
    GLuint VAO;
    GLuint VBO;
    Camera* camera;
    Transform* transform;
public:
    std::shared_ptr<Shader> shader;
    std::shared_ptr<Material> material;
    GLint vertices;
    
    MeshRender(const Mesh& mesh);

    void Start() override;
    void Render() override;
    
    std::unique_ptr<Component> Clone() override;

    ~MeshRender() override;
};