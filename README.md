# Camera-Tools/Photomode For Watch_Dogs
This is a tool that allows you to control the camera for Watch_Dogs, and allows you to control many other elements of the Disrupt engine to allow for a definitive "picture mode" for taking screenshots. <br /> 
The files in Binaries go in your gamedir/bin where your Watch_Dogs executable (.exe) is. 
# Important Notes
• This was hard-coded for the current latest version of Watch_Dogs for Ubisoft Connect/Uplay. This will not work with any other version of the game. <br /> 
• If you have the Watch_Dogs on Steam, backup your original Disrupt_b64.dll, and replace it with the one included in the Binaries Folder. The DLLs don't have any real differences in terms of functionality.  <br /> 
• If you are using a cracked version of Watch_Dogs, replacing Disrupt_b64.dll may or may not break your crack, as some cracks are included directly in the Disrupt DLL.
# Notes for those using the source code in Visual Studio
### Apparently since the solution files don't seem to do this on their own  <br /> 
• Disable Precompiled Headers for both DLLs under Properties/Precompiled Headers.  <br /> 
• If something isn't working, try changing the language standard under Properties/Language.  <br /> 
• I used "Preview - Features from the Latest C++ Working Draft (/std:c++latest)" as the language standard, however, I am using Visual Studio 2019.  <br /> 
• Make sure you are targetting x64 platform. 
# Features
• Control the camera including the field of view and camera roll. <br /> 
• Control the depth of field, with two modes allowing you to blur near objects and/or objects in the distance. <br /> 
• Control the time of day as well as the weather preset. <br /> 
• Freeze and slow down the game. <br /> 
• UI/HUD Toggle.  <br /> 
• Super Rendering Toggle, which renders the game at an extreme quality only seen in pre rendered cutscenes. This toggle assumes you are already running the game on Ultra settings.
# Acknowledgments
This project uses a function coded by github.com/yubie-re in order to allow me to change read/write protections in certain memory regions protected by the game's DRM. 
# Extra
Super Rendering Demo: https://youtu.be/oghZN1t39YM  <br />
Join The Watch_Dogs Modding Discord: https://discord.gg/4TFmTnunzv
