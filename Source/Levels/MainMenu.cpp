#include <Urho3D/Urho3DAll.h>
#include "MainMenu.h"
#include "../MyEvents.h"
#include <string>

using namespace Levels;

    /// Construct.
MainMenu::MainMenu(Context* context) :
    BaseLevel(context)
{
}

MainMenu::~MainMenu()
{
}

void MainMenu::Init()
{
    if (data_.Contains("Message")) {
        //SharedPtr<Urho3D::MessageBox> messageBox(new Urho3D::MessageBox(context_, data_["Message"].GetString(), "Oh crap!"));
        VariantMap data;
        data["Title"] = "Error!";
        data["Message"] = data_["Message"].GetString();
        SendEvent("ShowAlertMessage", data);
    }
    BaseLevel::Init();

    // Create the scene content
    CreateScene();

    // Create the UI content
    CreateUI();

    // Subscribe to global events for camera movement
    SubscribeToEvents();
    VariantMap data;
    data["Message"] = "Entered menu!";
    SendEvent("NewAchievement", data);

    data["Title"] = "Error!";
    data["Message"] = "Seems like everything is ok!";
    SendEvent("ShowAlertMessage", data);
}

void MainMenu::CreateScene()
{
    
}

void MainMenu::CreateUI()
{
    UI* ui = GetSubsystem<UI>();

    //////////////
    _startButton = ui->GetRoot()->CreateChild<Button>();
    _startButton->SetSize(IntVector2(100, 30));
    _startButton->SetStyleAuto();

    _startButton->SetAlignment(HA_CENTER, VA_CENTER);

    Text* text = _startButton->CreateChild<Text>();
    text->SetText("Start game!");
    text->SetStyleAuto();
    text->SetAlignment(HA_CENTER, VA_CENTER);
}

void MainMenu::SubscribeToEvents()
{
    SubscribeToEvent(E_UPDATE, URHO3D_HANDLER(MainMenu, HandleUpdate));
    SubscribeToEvent("KeyDown", URHO3D_HANDLER(MainMenu, HandleKeyDown));
    SubscribeToEvent(_startButton, E_RELEASED, URHO3D_HANDLER(MainMenu, HandleStartGame));
}

void MainMenu::HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    Input* input = GetSubsystem<Input>();
    if (!input->IsMouseVisible()) {
        input->SetMouseVisible(true);
    }
}

void MainMenu::HandleKeyDown(StringHash eventType, VariantMap& eventData)
{
    int key = eventData["Key"].GetInt();

    // Toggle console by pressing F1
    if (key == KEY_F2) {
        VariantMap data;
        data["Name"] = "SettingsWindow";
        SendEvent(MyEvents::E_OPEN_WINDOW, data);
    }
}

void MainMenu::HandleStartGame(StringHash eventType, VariantMap& eventData)
{
    VariantMap& levelEventData = GetEventDataMap();
    levelEventData["Name"] = "Loading";
    SendEvent(MyEvents::E_SET_LEVEL, levelEventData);
}