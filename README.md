# RED SIGNAL

A polyphonic Sovietwave / retrowave software synthesizer built with JUCE 8.0.8.
This project builds **VST3 x64 for Windows**. No VST2 or VST3 SDK download is required.

## Instrument

- 3 oscillators per voice: sine, saw, square, triangle and noise
- 8-voice polyphony
- Low-pass, high-pass and band-pass filter
- Amp envelope and filter envelope
- Chorus, stereo delay (with ping-pong mode), reverb and master soft clipping
- MIDI input, pitch bend and sustain pedal
- 60 factory presets in six categories: BASS, LEAD, PAD, KEYS, SFX and OTHER
- Host automation and project-state recall through JUCE AudioProcessorValueTreeState

## Build automatically on GitHub (recommended)

The repository includes a GitHub Actions workflow at `.github/workflows/build-windows.yml`.
It compiles the plugin on a GitHub-hosted Windows x64 runner and uploads a ZIP containing
the complete `RED SIGNAL.vst3` bundle.

1. Create or open a GitHub repository and upload **all files and folders** from this project.
   Make sure the `.github/workflows/build-windows.yml` file is included. If using the GitHub
   web interface, create the `.github` and `workflows` folders and add `build-windows.yml`.
2. Commit/push the files. The workflow starts automatically on every push. You can also open
   the repository's **Actions** tab, select **Build RED SIGNAL VST3**, and choose **Run workflow**.
3. Open the completed workflow run. At the bottom, under **Artifacts**, download
   `RED-SIGNAL-Windows-x64-VST3`.
4. Extract the ZIP. It contains the complete `RED SIGNAL.vst3` folder and `BUILD-INFO.txt`.

The first build downloads the pinned JUCE 8.0.8 source using CMake FetchContent, so the runner
needs access to GitHub. No JUCE SDK needs to be added to this repository manually.

## Build locally on Windows x64

Requirements:

- Visual Studio 2022 or newer with the **Desktop development with C++** workload
- CMake 3.22+
- Git (used by CMake FetchContent to obtain the pinned JUCE 8.0.8 source, unless a local `JUCE` folder is supplied)

From the project folder, run:

```bat
build-win64.bat
```

Or use PowerShell:

```powershell
cmake -S . -B build -A x64
cmake --build build --config Release --parallel 4
```

The resulting VST3 bundle is expected at:

```text
build/RedSignal_artefacts/Release/VST3/RED SIGNAL.vst3
```

Copy the **entire `RED SIGNAL.vst3` folder**, not just the binary inside `Contents/x86_64-win`.

## Install in FL Studio 26

FL Studio scans VST3 plugins from its standard VST3 locations. Its custom Plugin Search Paths are intended for VST1/VST2, not arbitrary VST3 folders. A VST3 bundle placed in an arbitrary folder such as `D:\Audio\VST3` may not be discovered just by adding that folder to the custom search-path list.

### Standard install

Copy the complete bundle to:

```text
C:\Program Files\Common Files\VST3\RED SIGNAL.vst3
```

Then open **Options → Manage plugins** and click **Find installed plugins**.

### Keep the actual plugin files on another drive

If you do not want the plugin's files physically stored on C:, keep the bundle on another drive and create a Windows directory junction from the standard VST3 location to it. For example, place the bundle here:

```text
D:\Audio\VST3\RED SIGNAL.vst3
```

Then open **Command Prompt as Administrator** and run:

```bat
if not exist "C:\Program Files\Common Files\VST3" mkdir "C:\Program Files\Common Files\VST3"
mklink /J "C:\Program Files\Common Files\VST3\RED SIGNAL.vst3" "D:\Audio\VST3\RED SIGNAL.vst3"
```

This creates only a directory link in the standard location; the actual plugin bundle remains on D:. FL Studio sees it through the standard VST3 path. Replace `D:\Audio\VST3` with the folder you actually use. Do not create a junction if a `RED SIGNAL.vst3` folder already exists at the link location.

## Presets

The factory bank is compiled into the plugin, so factory presets travel with the VST3 bundle and do not depend on its install location. FL Studio project state stores the active parameter values.
