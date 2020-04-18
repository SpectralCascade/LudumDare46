#include "gui.h"
#include "gamecontroller.h"
#include "simulator.h"

using namespace Ossium;

REGISTER_COMPONENT(GUI);

void GUI::OnCreate()
{
    GraphicComponent::OnCreate();
    input = entity->AddComponent<InputGUI>();

    // build server button
    buildServerButton = entity->CreateChild()->AddComponent<Button>();
    buildServerButton->sprite->AddState(
        "default",
        GetService<ResourceController>()->Get<Image>("assets/build_server_button.png", *GetService<Renderer>(), SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC),
        true,
        3
    );

    // pause button
    pauseButton = entity->CreateChild()->AddComponent<Button>();
    pauseButton->sprite->AddState(
        "pause",
        GetService<ResourceController>()->Get<Image>("assets/pause.png", *GetService<Renderer>(), SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC),
        true,
        3
    );
    pauseButton->sprite->AddState(
        "play",
        GetService<ResourceController>()->Get<Image>("assets/play.png", *GetService<Renderer>(), SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC),
        true,
        3
    );

    input->AddInteractable(SID("BuildServer")::str, *buildServerButton);
    input->AddInteractable(SID("PausePlay")::str, *pauseButton);

    buildServerButton->GetTransform()->SetWorldPosition(Vector2(50, (768 / 2) + 60));
    pauseButton->GetTransform()->SetWorldPosition(Vector2(1280 / 2, 768 - 50));

    SetRenderLayer(8);

}

void GUI::Render(Renderer& renderer)
{
    Font* font = GetService<ResourceController>()->Get<Font>("assets/Orkney Regular.ttf", 96);
    moneyText.SetBounds(Vector2(1000, 1000));
    moneyText.SetPointSize(36);
    moneyText.SetText(renderer, *font, Utilities::Format("<b>Money: ${0}</b>", game->simulator->money), true);
    moneyText.Update(*font);
    moneyText.Render(renderer, *font, Vector2(10, 768 - 60));


    timeText.SetBounds(Vector2(1000, 1000));
    timeText.SetPointSize(36);
    timeText.SetText(renderer, *font, Utilities::Format("<b>Day {0}</b>", game->simulator->GetTimeStep()), true);
    timeText.Update(*font);
    timeText.Render(renderer, *font, Vector2(1280 - 200, 768 - 60));

}