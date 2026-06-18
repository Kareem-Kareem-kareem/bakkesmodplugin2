# Remove any stale SDK folder
if (Test-Path C:\sdk) { Remove-Item -Recurse -Force C:\sdk }

# Download the official SDK zip from the latest release
$url = "https://github.com/bakkesmodorg/BakkesModSDK/releases/download/v1.0/sdk.zip"
$zip = "sdk.zip"
Write-Host "Downloading SDK from $url"
Invoke-WebRequest -Uri $url -OutFile $zip -UserAgent "Mozilla/5.0"

# Extract to C:\sdk
Write-Host "Extracting to C:\sdk"
Expand-Archive -Path $zip -DestinationPath C:\sdk -Force
Remove-Item $zip

# Check if the files are in a subfolder (e.g., "BakkesModSDK-...")
$subfolders = Get-ChildItem C:\sdk -Directory
if ($subfolders.Count -eq 1 -and (Test-Path "C:\sdk\$($subfolders[0].Name)\include\bakkesmod\plugin\bakkesmodplugin.h")) {
    # Move everything up one level
    Write-Host "Moving files from subfolder to root..."
    $temp = "C:\sdk_temp"
    Move-Item C:\sdk\* $temp -Force
    Remove-Item C:\sdk -Force
    Move-Item $temp C:\sdk -Force
}

# Verify the header exists
$header = "C:\sdk\include\bakkesmod\plugin\bakkesmodplugin.h"
if (-not (Test-Path $header)) {
    Write-Error "Header not found at $header – extraction failed."
    exit 1
}

# Verify the lib exists
$lib = "C:\sdk\lib\BakkesModPlugin.lib"
if (-not (Test-Path $lib)) {
    # Try alternate location
    $lib = "C:\sdk\lib\Release\BakkesModPlugin.lib"
    if (-not (Test-Path $lib)) {
        Write-Error "BakkesModPlugin.lib not found."
        exit 1
    }
    # Copy it to the expected location
    Copy-Item $lib C:\sdk\lib\ -Force
}

# Set environment variable for CMake
$env:BAKKESMOD_SDK = "C:\sdk"

# Build the plugin
Write-Host "Building plugin..."
New-Item -ItemType Directory -Path build -Force | Out-Null
Push-Location build
cmake .. -G Ninja
if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
cmake --build . --config Release
if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
Pop-Location

Write-Host "Build succeeded! DLL is in build/Release/"
