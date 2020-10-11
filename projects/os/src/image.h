
char imageSel = 127;
callback *iPrev, *iNext;

void ImageDisplay()
{
	// Clear screen and callbacks first!
	ClearScreen();
	
	// Select file, and display it
	LoadBitmap(fileNames[imageSel]);
	
	// Add Taskbar
	DrawTaskBar();
	
	// Display file name
	paperColor = WHITE; inkColor = BLACK; 
	PrintStr(14, CHR_ROWS-1, fileNames[imageSel]);		
	
	// Add L/R Controllers
	paperColor = BLACK; inkColor = WHITE;
	iPrev = Button(10, CHR_ROWS-1, 3, 1, " ( ");	
	iNext = Button(27, CHR_ROWS-1, 3, 1, " ) ");		
}

void ImageScreen()
{		
	if (imageSel == 127)
		SelectFile(1, imageExt, &imageSel);
	ImageDisplay();
}

void ImageCallback(callback* call)
{	
	// Select next file in chosen direction
	char dir = 1;
	if (call == iPrev)
		dir = -1;
	SelectFile(dir, imageExt, &imageSel);
	ImageDisplay();
}
