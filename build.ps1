# Clean any previous SDK
if (Test-Path C:\sdk) { Remove-Item -Recurse -Force C:\sdk }

# Clone SDK
git clone --depth 1 https://github.com/bakkesmodorg/BakkesModSDK.git C:\sdk

# Build SDK (generates BakkesModPlugin.lib)
Push-Location C:\sdk
New-Item -ItemType Directory -Path build -Force | Out-Null
Set-Location build
cmake .. -G Ninja
if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
cmake --build . --config Release
if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }

# Copy the .lib to a standard location
New-Item -ItemType Directory -Path C:\sdk\lib -Force | Out-Null
Copy-Item Release\BakkesModPlugin.lib C:\sdk\lib\ -Force

# Verify the header exists
$header = "C:\sdk\include\bakkesmod\plugin\bakkesmodplugin.h"
if (-not (Test-Path $header)) {
    Write-Error "Header not found at $header"
    exit 1
}

# Set environment variable for CMake
$env:BAKKESMOD_SDK = "C:\sdk"

# Go back to repo root
Pop-Location

# Build the plugin
New-Item -ItemType Directory -Path build -Force | Out-Null
Set-Location build
cmake .. -G Ninja
if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
cmake --build . --config Release
if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
Pop-Location

Write-Host "Build succeeded! DLL is in build/Release/"
