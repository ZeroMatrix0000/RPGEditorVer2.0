```mermaid

classDiagram

namespace Renderings{
    class ICameraScreen
    class CameraScreen
    class DeviceResources
    class RenderingResources
    class Model3DSource
    class Model3D
    class IModel3DRenderer
    class Model3DRenderer
}

namespace Systems{
    class IResources
    class Resources
    class IWindowController
    class WindowController
}

namespace GameObjects{
    class Observer
    class ComponentCreatePermit
    class Component
    class ComponentFactory
    class GameObject
    class Transform
}

namespace Scenes{
    class Scene["Scene&lt;TTransitionData, TContext>"]
    class ISceneManager["ISceneManager&lt;TTransitionData>"]
    class SceneManager["SceneManager&lt;TTransitionData, TContext>"]
}

<<OnlyOne>> DeviceResources
<<OnlyOne>> RenderingResources
<<OnlyOne>> IModel3DRenderer
<<OnlyOne>> IResources
<<OnlyOne>> IWindowController
<<OnlyOne>> ComponentCreatePermit
<<OnlyOne>> ComponentFactory
<<OnlyOne>> ISceneManager

Component <|-- ICameraScreen
ICameraScreen <|-- CameraScreen
ICameraScreen --o Model3D
Model3DSource "*" --* "1" Resources
Model3D o-- IModel3DRenderer
Model3D "*" --o "1" Model3DRenderer
Component <|-- Model3D
IModel3DRenderer <|-- Model3DRenderer
IModel3DRenderer --o ComponentFactory
IResources --o Model3DRenderer
IResources <|-- Resources
IWindowController <|-- WindowController
Observer <|-- Component
ComponentCreatePermit --* ComponentFactory
ComponentCreatePermit <.. Component
Component o-- GameObject
Component "*" --* "1" GameObject
Component <|-- Transform
Component <|-- Scene
ComponentFactory <.. GameObject
Scene --o SceneManager
ISceneManager <|-- SceneManager

```

```mermaid

classDiagram

namespace Renderings{
    class DeviceResources
    class RenderingResources
    class Model3DRenderer
}

namespace Systems{
    class Resources
}

namespace GameObjects{
    class ComponentFactory
    class GameObject
}

namespace Scenes{
    class Scene["Scene&lt;TTransitionData, TContext>"]
    class ISceneManager["ISceneManager&lt;TTransitionData>"]
    class SceneManager["SceneManager&lt;TTransitionData, TContext>"]
}

class GameContext
class SceneTransitionData
class Game

class SampleScene

<<OnlyOne>> DeviceResources
<<OnlyOne>> RenderingResources
<<OnlyOne>> Model3DRenderer
<<OnlyOne>> ComponentFactory
<<OnlyOne>> ISceneManager
<<OnlyOne>> SceneManager
<<OnlyOne>> GameContext
<<OnlyOne>> Game

DeviceResources --* Game
RenderingResources --* Game
Model3DRenderer --* Game
Resources --* Game
ComponentFactory --o GameContext
ComponentFactory --* Game
GameObject "*" --* "1" SampleScene
Scene <|-- SampleScene
ISceneManager --o GameContext
SceneManager --* Game
GameContext --* Game
GameContext <.. SampleScene
SceneTransitionData <.. SampleScene

```
