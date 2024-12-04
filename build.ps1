# build.ps1

g++ "maincopy.cpp" "gridcopy.cpp" "colorscopy.cpp" "gamecopy.cpp"  -o main.exe -lraylib -lopengl32 -lgdi32 -lwinmm

# Check if the compilation was successful
if ($LASTEXITCODE -eq 0) {
    Write-Host "Compilation successful! Running game..."
    .\main.exe .\test.txt
} else {
    Write-Host "Compilation failed."
}
