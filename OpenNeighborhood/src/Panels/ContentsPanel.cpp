#include "pch.h"
#include "Panels/ContentsPanel.h"

#include "Render/TextureManager.h"
#include "Elements/AddXboxButton.h"

ContentsPanel::ContentsPanel()
{
	TextureManager::AddTexture("addXboxButton", "assets/icons/addXboxButton.png");

	m_Elements.push_back(std::make_shared<AddXboxButton>());

	UpdateEventCallbacks();
}

void ContentsPanel::OnRender()
{
	float pathPanelSize = m_Margin * 5.0f;

	ImGuiWindowFlags windowFlags =
		  ImGuiWindowFlags_NoTitleBar
		| ImGuiWindowFlags_NoCollapse
		| ImGuiWindowFlags_NoResize
		| ImGuiWindowFlags_NoMove
		| ImGuiWindowFlags_NoBringToFrontOnFocus
		| ImGuiWindowFlags_NoNavFocus
	;

	ImGui::SetNextWindowPos(ImVec2(m_Margin, m_Margin * 2.0f + pathPanelSize));
	ImGui::SetNextWindowSize(ImVec2((float)m_WindowWidth - m_Margin * 2.0f, (float)m_WindowHeight - (m_Margin * 3.0f + pathPanelSize)));

	ImGui::Begin("Contents Window", nullptr, windowFlags);

	for (auto& element : m_Elements)
		element->OnRender();

	ImGui::End();
}

void ContentsPanel::OnEvent(Event& event)
{
	Panel::OnEvent(event);

	EventDispatcher dispatcher(event);
	dispatcher.Dispatch<ContentsChangeEvent>(BIND_EVENT_FN(ContentsPanel::OnContentsChange));
}

bool ContentsPanel::OnContentsChange(ContentsChangeEvent& event)
{
	if (event.Append())
	{
		m_Elements.reserve(m_Elements.size() + event.GetElements()->size());
		m_Elements.insert(m_Elements.end(), event.GetElements()->begin(), event.GetElements()->end());
	}
	else
	{
		m_Elements = *event.GetElements();
	}

	return true;
}

void ContentsPanel::UpdateEventCallbacks()
{
	for (auto& element : m_Elements)
		element->SetEventCallback(BIND_EVENT_FN(ContentsPanel::OnEvent));
}
