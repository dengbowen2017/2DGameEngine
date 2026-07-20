//#include <SDL3/SDL.h>
//#include <iostream>
//
//#include "Game/Game.h"
//#include "Game/GameObject.h"
//#include "Game/Component.h"
//
//int main(int argc, char* argv[]) {
//    if (!SDL_Init(SDL_INIT_VIDEO)) {
//        std::cerr << "SDL 初始化失败: " << SDL_GetError() << std::endl;
//        return -1;
//    }
//
//    SDL_Window* window = nullptr;
//    SDL_Renderer* renderer = nullptr;
//
//  
//    if (!SDL_CreateWindowAndRenderer("2D Game Engine", 800, 600, 0, &window, &renderer)) {
//        std::cerr << "创建窗口/渲染器失败: " << SDL_GetError() << std::endl;
//        SDL_Quit();
//        return -1;
//    }
//
//    // 3. 游戏/应用主循环控制变量
//    bool isRunning = true;
//    SDL_Event event;
//
//    GE::Game game;
//    GE::GameObject go = game.CreateGameObject();
//    go.AddComponent<GE::TransformComponent>(50.f, 50.f);
//    auto& trans = go.GetComponent<GE::TransformComponent>();
//    // 定义一个要在屏幕上绘制的矩形（SDL3 推荐使用 float 类型的 FRect）
//
//  
//    // 4. 主循环 (Game Loop)
//    while (isRunning) {
//        // --- 4a. 事件处理 (Event Handling) ---
//        while (SDL_PollEvent(&event)) {
//            if (event.type == SDL_EVENT_QUIT) {
//                isRunning = false;
//            }
//        }
//
//        // --- 4b. 状态更新 (Update) ---
//        // 这里可以写你的游戏逻辑，比如让矩形移动：
//        // rect.x += 0.01f; 
//        trans.x += 0.01f;
//        trans.y += 0.01f;
//
//        // --- 4c. 渲染图形 (Render) ---
//        
//        SDL_FRect rect = { trans.x, trans.y, 100.0f, 100.0f };
//
//        // 步骤一：设置清屏颜色（这里设为深蓝色：R=20, G=30, B=50）
//        SDL_SetRenderDrawColor(renderer, 20, 30, 50, 255);
//        // 执行清屏
//        SDL_RenderClear(renderer);
//
//        // 步骤二：设置画笔颜色并绘制填充矩形（这里设为绿色）
//        SDL_SetRenderDrawColor(renderer, 46, 204, 113, 255);
//        SDL_RenderFillRect(renderer, &rect);
//
//        // 步骤三：把后台缓冲区的内容“翻”到屏幕上显示
//        SDL_RenderPresent(renderer);
//    }
//
//    // 5. 清理资源 (Cleanup)
//    // 遵循“后创建先销毁”的原则
//    SDL_DestroyRenderer(renderer);
//    SDL_DestroyWindow(window);
//    SDL_Quit();
//
//    return 0;
//}

#include "Game.h"

int main()
{
	VS::Game game;
	game.Run();
}