RequestExecutionLevel admin

Name "VERA 0.4beta1"
outfile "vera0.4_beta1_install.exe"


installDir $PROGRAMFILES\VERA

	DirText "To install VERA 0.4beta1, please choose a directory."

# open section
section


	setOutPath $INSTDIR

	file .\demo.zip
	file .\freetype6.dll
	file .\glut32.dll
	file .\pin.exe
	file .\pindb.exe
	file .\pinvm.dll
	file .\taipin.dll
	file .\vera.ico
	file .\vera_ida.plw
	file .\vera-manual.pdf
	file .\veratrace.dll
	file .\wxVera.exe
	file .\zlib1.dll
	file .\vcredist_x86.exe
	



	WriteUninstaller $INSTDIR\vera0.4beta1_uninstall.exe
 	ExecWait "$INSTDIR\vcredist_x86.exe"

	CreateDirectory "$SMPROGRAMS\VERA"
	CreateShortCut "$SMPROGRAMS\VERA\VERA 0.4beta1.lnk" "$INSTDIR\wxVera.exe"
	CreateShortCut "$DESKTOP\VERA 0.4beta1.lnk" "$INSTDIR\wxVera.exe"

sectionEnd




Section "Uninstall"

	Delete $INSTDIR\vera0.4beta_uninstall.exe


	Delete $INSTDIR\demo.zip
	Delete $INSTDIR\freetype6.dll
	Delete $INSTDIR\glut32.dll
	Delete $INSTDIR\pin.exe
	Delete $INSTDIR\pindb.exe
	Delete $INSTDIR\pinvm.dll
	Delete $INSTDIR\taipin.dll
	Delete $INSTDIR\vera.ico
	Delete $INSTDIR\vera_ida.plw
	Delete $INSTDIR\vera-manual.pdf
	Delete $INSTDIR\veratrace.dll
	Delete $INSTDIR\wxVera.exe
	Delete $INSTDIR\zlib1.dll



	RMDIR $INSTDIR

	Delete "$SMPROGRAMS\VERA\VERA 0.4beta1.lnk"
	RMDIR "$SMPROGRAMS\VERA\"

	Delete "$DESKTOP\VERA 0.4beta.lnk"
SectionEnd
