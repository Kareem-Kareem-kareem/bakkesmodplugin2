# Download SDK zip from GitHub release
$url = "https://github.com/bakkesmodorg/BakkesModSDK/releases/download/v1.0/sdk.zip"
Invoke-WebRequest -Uri $url -OutFile sdk.zip -UserAgent "Mozilla/5.0"

# Extract – it creates a folder like BakkesModSDK-1.0
Expand-Archive sdk.zip -DestinationPath C:\

# Find that folder and move contents to C:\sdk
$src = Get-ChildItem C:\ -Directory | Where-Object Name -match "BakkesModSDK" | Select-Object -First 1
if ($src) {
    Move-Item "$($src.FullName)\*" C:\sdk -Force
    Remove-Item $src.FullName -Force
} else {
    # If it extracted directly, ensure we have C:\sdk
    if (-not (Test-Path C:\sdk)) { New-Item -ItemType Directory C:\sdk -Force }
}

# Verify headers
$header = "C:\sdk\include\bakkesmod\plugin\bakkesmodplugin.h"
if (-not (Test-Path $header)) { Write-Error "Header missing"; exit 1 }

# Find BakkesModPlugin.lib (could be in subfolders)
$lib = Get-ChildItem C:\sdk\lib -Recurse -Filter BakkesModPlugin.lib | Select-Object -First 1
if (-not $lib) { Write-Error "Lib missing"; exit 1 }
New-Item -ItemType Directory -Path C:\sdk\lib -Force | Out-Null
Copy-Item $lib.FullName C:\sdk\lib\ -Force

# Set env for CMake
$env:BAKKESMOD_SDK = "C:\sdk"

# Build the plugin
New-Item -ItemType Directory -Path build -Force | Out-Null
Push-Location build
cmake .. -G Ninja
if ($LASTEXITCODE) { exit $LASTEXITCODE }
cmake --build . --config Release
if ($LASTEXITCODE) { exit $LASTEXITCODE }
Pop-Location
Write-Host "✅ Build complete"
