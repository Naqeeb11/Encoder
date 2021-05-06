# You can run this code using **codeblocks** configured with **opengl**.
  Follow below for environment setup and execution of code.

# Install OpenGL on windows in CodeBlocks

1. Download code block and install it.
2. Go to the link and download zip file from the download link that appears after freeglut
   MinGW package with having link name as Download freeglut 3.0.0 for MinGW and extract
   it.
3. Open notepad with run as administrator and open file from.

  - This PC / C:(C-drive) Program Files(x86) / CodeBlocks / share / CodeBlocks / templates, (then click to show All Files).
  - Next, open glut.cbp and search all glut32 and replace with freeglut.
  - Then, open from This PC / C:(C-drive) / Program Files(x86) / CodeBlocks / share /
      CodeBlocks / templates / wizard / glut (then click to show All Files)
  - Open wizard.script and here, also replace all glut32 with freeglut
  
4. Then go to freeglut folder (where it was downloaded) and

- Include / GL and copy all four file from there
- Go to This PC / C:(C-drive) / Program Files(x86) / CodeBlocks / MinGW / include
/ GL and paste it.
- Then, from download folder freeglut / lib, copy two files and go to This PC / C:(C-drive)
/ Program Files(x86) / CodeBlocks / MinGW / lib and paste it.
- Again go to downloaded folder freeglut / bin and copy one file (freeglut.dll) from here
and go to This PC / C:(C-drive) / Windows / SysWOW64 and paste this file.

5. Now open Code::Blocks.

- Select File / New Project / GLUT project / Next.
- Give project title anything and then choose Next.
- For selecting GLUT’s location : This PC / C:(C-drive) / Program Files(x86) / CodeBlocks / MinGW.
- Press OK / Next / Finish.

Now, Code::Blocks is ready to test for OpenGL File.
Finally to run code copy our source code in main file of new project.
