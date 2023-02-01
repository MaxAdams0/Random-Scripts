if (Test-Path "final") {
    Write-Host "dir 'final' already exists"
} else {
    New-Item -ItemType Directory -Path "final"
}

if (Test-Path "frames") {
    Write-Host "If you see this that means this script is assuming you already have the .jpg's in the 'frames' dir"
} else {
    New-Item -ItemType Directory -Path "frames"
    ffmpeg -i "badapple.mp4" "frames\%06d.jpg"
}

$thisDir = (Get-Item .).FullName
$framesDir = $thisDir + "\frames\"
$jpgFiles = Get-ChildItem -Path $framesDir -Filter "*.jpg" -File

# Set the path of the shortcut file
$shortcutPath = $thisdir + "\final" + "\shortcut_file.lnk"

# Create the shortcut
$WshShell = New-Object -ComObject WScript.Shell
$shortcut = $WshShell.CreateShortcut($shortcutPath)

# Set the target path of the shortcut
$shortcut.TargetPath = $framesDir + "000001.jpg"

# Save the shortcut
$shortcut.Save()

foreach ($file in $jpgFiles) {
    $fullpath = $dir + $file
    $shortcut.TargetPath = $framesDir + $file
    $shortcut.Save()
    Start-Sleep -Milliseconds 16
    Write-Host Set shortcut path to: $file
}