#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <bits/stdc++.h>

using namespace std;

//function declaration
void display();
void NRZL();
void NRZI();
void Manchester();
void DManchester();
void AMI();
void B8ZS();
void HDB3();
void LCS(int);
void reshape(int, int);

unordered_set<int> ar;
string str;

//text configuration
void drawText(const char *text, int length, int x, int y, char t = 'o')
{
    glMatrixMode(GL_PROJECTION);
    double *matrix = new double[16];
    glGetDoublev(GL_PROJECTION_MATRIX, matrix);
    glLoadIdentity();
    glOrtho(0, 200, -100, 100, -5, 5);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glLoadIdentity();
    glRasterPos2i(x, y);

    for (int i = 0; i < length; i++)
    {
        if (t == 'o')
            glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)text[i]);
        else
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, (int)text[i]);
    }
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixd(matrix);
    glMatrixMode(GL_MODELVIEW);
}

//output window configuration
void init()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
}

void windowsInitialisation(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);

    glutInitWindowPosition(80, 50);
    glutInitWindowSize(1400, 700);

    glutCreateWindow("ENCODING SCHEMES");
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 200, -100, 100);
    glMatrixMode(GL_MODELVIEW);
}

//binary string generation
void generateRandomString(int l)
{
    srand(time(0));
    for (int i = 0; i < l; i++)
        str = str + ((rand() % 2 == 0) ? '0' : '1');
}

void generateStringCsubseq(int l)
{
    string s[] = {"11111", "00000000", "000000000", "1111111", "0000000"};
    srand(time(0));

    while (l > 0)
    {
        int randomIndex = rand() % 5;
        int r = rand();
        if (l >= 10 && r % 3 == 0)
        {
            str = str + s[randomIndex];
            l = l - s[randomIndex].length();
        }
        else
        {
            str = str + ((randomIndex % 2 == 0) ? '0' : '1');
            l--;
        }
    }
}

// Manacher's Algorithm - Linear Time O(n) Longest Palindromic Substring (reference geeksforgeeks)

void findLongestPalindromicString()
{
    int N = str.length();
    if (N == 0)
        return;
    N = 2 * N + 1; //Position count
    int L[N];      //LPS Length Array
    L[0] = 0;
    L[1] = 1;
    int C = 1;   //centerPosition
    int R = 2;   //centerRightPosition
    int i = 0;   //currentRightPosition
    int iMirror; //currentLeftPosition
    int expand = -1;
    int diff = -1;
    int maxLPSLength = 0;
    int maxLPSCenterPosition = 0;
    int start = -1;
    int end = -1;

    for (i = 2; i < N; i++)
    {
        //get currentLeftPosition iMirror for currentRightPosition i
        iMirror = 2 * C - i;
        //Reset expand - means no expansion required
        expand = 0;
        diff = R - i;
        //If currentRightPosition i is within centerRightPosition R
        if (diff >= 0)
        {
            if (L[iMirror] < diff) // Case 1
                L[i] = L[iMirror];
            else if (L[iMirror] == diff && R == N - 1) // Case 2
                L[i] = L[iMirror];
            else if (L[iMirror] == diff && R < N - 1) // Case 3
            {
                L[i] = L[iMirror];
                expand = 1; // expansion required
            }
            else if (L[iMirror] > diff) // Case 4
            {
                L[i] = diff;
                expand = 1; // expansion required
            }
        }
        else
        {
            L[i] = 0;
            expand = 1; // expansion required
        }

        if (expand == 1)
        {
            //Attempt to expand palindrome centered at currentRightPosition i
            //Here for odd positions, we compare characters and
            //if match then increment LPS Length by ONE
            //If even position, we just increment LPS by ONE without
            //any character comparison
            while (((i + L[i]) < N && (i - L[i]) > 0) &&
                   (((i + L[i] + 1) % 2 == 0) ||
                    (str[(i + L[i] + 1) / 2] == str[(i - L[i] - 1) / 2])))
            {
                L[i]++;
            }
        }

        if (L[i] > maxLPSLength) // Track maxLPSLength
        {
            maxLPSLength = L[i];
            maxLPSCenterPosition = i;
        }

        // If palindrome centered at currentRightPosition i
        // expand beyond centerRightPosition R,
        // adjust centerPosition C based on expanded palindrome.
        if (i + L[i] > R)
        {
            C = i;
            R = i + L[i];
        }
    }
    start = (maxLPSCenterPosition - maxLPSLength) / 2;
    end = start + maxLPSLength - 1;
    cout << "\nLongest Palindrome  of a given string is: ";
    for (i = start; i <= end; i++)
        cout << str[i];
    cout << "\n";
}

//O(n)
void LCS(int n)
{
    int x = 0;
    int l = str.length();
    for (int i = 0; i < l; i++)
    {
        if (str[i] == '0')
            x++;
        else
            x = 0;
        if (x == n)
        {
            ar.insert(i - n + 1);
            x = 0;
        }
    }
}

//partial partition
void linespace(int x)
{
    glPushAttrib(GL_ENABLE_BIT);
    glLineStipple(1, 0xAAAA);
    glEnable(GL_LINE_STIPPLE);
    glBegin(GL_LINES);

    glShadeModel(GL_FLAT);
    glColor3b(0.0, 0.0, 0.0);
    for (int i = -40; i <= 38; i = i + 4)
    {
        glVertex2f(x, i);
        glVertex2f(x, i + 2);
    }
    glEnd();
    glPopAttrib();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    glShadeModel(GL_SMOOTH);

    glBegin(GL_POLYGON);
    //background window configuration
    glColor3f(0.2, 0.4, 0.5);
    glVertex2f(0, 100);
    glVertex2f(0, -100);
    glVertex2f(200, -100);
    glVertex2f(200, 100);

    glEnd();

    glBegin(GL_LINE_STRIP);

    glShadeModel(GL_FLAT);
    glColor3b(0.0, 0.0, 0.0);
    glVertex2f(15, -40);
    glVertex2f(15, 38);

    glEnd();
    glFlush();
}

//initial graph config
void SetupOfGraph(string s, int x)
{
    int l = str.length();
    display();
    glColor3f(0.9, 0.5, 0.2);
    string scheme = s;
    drawText(scheme.data(), scheme.size(), x, 80, 'h');

    int i = 19;
    while (l--)
    {
        glColor3f(0.0, 0.0, 0.0);

        linespace(i);
        i = i + 4;
    }
}

//numbering in graph
void Notation()
{
    glColor3f(0.5, 0.0, 0.0);
    int d = 0;
    string text;
    int r = str.length();
    for (int i = 15; i <= r * 4 + 11; i = i + 4)
    {
        if (str[d++] == '0')
            text = " 0";
        else
            text = " 1";
        drawText(text.data(), text.size(), i, 20);
    }
}

void NRZL()
{
    SetupOfGraph("NRZ-L", 95);
    glBegin(GL_LINES);

    glShadeModel(GL_FLAT);
    int i = 15;
    int r = str.length();
    int d = 0;
    while (i <= r * 4 + 11)
    {
        glColor3f(0.0, 0.0, 0.0);

        glVertex2f(i, 0);
        glVertex2f(i + 4, 0);

        glColor3f(0.5, 0.0, 0.0);
        if (str[d] == '0')
        {
            glVertex2f(i, 10);
            glVertex2f(i + 4, 10);
        }

        else
        {
            glVertex2f(i, -10);
            glVertex2f(i + 4, -10);
        }
        if (d > 0 && str[d - 1] != str[d])
        {
            glVertex2f(i, 10);
            glVertex2f(i, -10);
        }
        i = i + 4;
        d++;
    }

    glColor3f(0.0, 0.0, 0.0);
    glVertex2f(i, 0);
    glVertex2f(i + 4, 0);

    glEnd();

    Notation();

    glFlush();
}

void NRZI()
{
    SetupOfGraph("NRZ-I", 95);
    int r = str.length();

    glBegin(GL_LINES);

    glShadeModel(GL_FLAT);
    int i = 15;
    int d = 0;
    int y1 = -10;

    while (i <= r * 4 + 11)
    {
        glColor3f(0.0, 0.0, 0.0);

        glVertex2f(i, 0);
        glVertex2f(i + 4, 0);

        glColor3f(0.5, 0.0, 0.0);
        if (str[d] == '0')
        {
            glVertex2f(i, y1);
            glVertex2f(i + 4, y1);
        }
        else
        {
            y1 = -y1;
            glVertex2f(i, y1);
            glVertex2f(i + 4, y1);
        }
        if (d > 0 && str[d] == '1')
        {
            glVertex2f(i, 10);
            glVertex2f(i, -10);
        }
        i = i + 4;
        d++;
    }

    glColor3f(0.0, 0.0, 0.0);
    glVertex2f(i, 0);
    glVertex2f(i + 4, 0);

    glEnd();

    Notation();

    glFlush();
}

void Manchester()
{
    SetupOfGraph("Manchester", 90);
    int r = str.length();

    glBegin(GL_LINES);

    glShadeModel(GL_FLAT);
    int i = 15;
    int d = 0;
    while (i <= r * 4 + 11)
    {
        glColor3f(0.0, 0.0, 0.0);

        glVertex2f(i, 0);
        glVertex2f(i + 4, 0);

        glColor3f(0.5, 0.0, 0.0);
        if (str[d] == '0')
        {
            glVertex2f(i, 10);
            glVertex2f(i + 2, 10);
            glVertex2f(i + 2, 10);
            glVertex2f(i + 2, -10);
            glVertex2f(i + 2, -10);
            glVertex2f(i + 4, -10);
        }

        else
        {
            glVertex2f(i, -10);
            glVertex2f(i + 2, -10);
            glVertex2f(i + 2, -10);
            glVertex2f(i + 2, 10);
            glVertex2f(i + 2, 10);
            glVertex2f(i + 4, 10);
        }
        if (d > 0 && str[d - 1] == str[d])
        {
            glVertex2f(i, 10);
            glVertex2f(i, -10);
        }
        i = i + 4;
        d++;
    }

    glColor3f(0.0, 0.0, 0.0);
    glVertex2f(i, 0);
    glVertex2f(i + 4, 0);

    glEnd();

    Notation();

    glFlush();
}

void DManchester()
{
    SetupOfGraph("Differential - Manchester", 80);
    int r = str.length();

    glBegin(GL_LINES);

    glShadeModel(GL_FLAT);
    int i = 15;
    int d = 0;
    int y1 = -10;
    while (i <= r * 4 + 11)
    {
        glColor3f(0.0, 0.0, 0.0);

        glVertex2f(i, 0);
        glVertex2f(i + 4, 0);

        glColor3f(0.5, 0.0, 0.0);
        if (str[d] == '0')
        {
            glVertex2f(i, y1);
            glVertex2f(i + 2, y1);
            glVertex2f(i + 2, y1);
            glVertex2f(i + 2, -y1);
            glVertex2f(i + 2, -y1);
            glVertex2f(i + 4, -y1);
        }

        else
        {
            y1 = -y1;
            glVertex2f(i, y1);
            glVertex2f(i + 2, y1);
            glVertex2f(i + 2, y1);
            glVertex2f(i + 2, -y1);
            glVertex2f(i + 2, -y1);
            glVertex2f(i + 4, -y1);
        }

        if (str[d] == '0')
        {
            glVertex2f(i, 10);
            glVertex2f(i, -10);
        }
        i = i + 4;
        d++;
    }

    glColor3f(0.0, 0.0, 0.0);
    glVertex2f(i, 0);
    glVertex2f(i + 4, 0);

    glEnd();

    Notation();

    glFlush();
}

void AMI()
{
    SetupOfGraph("AMI", 95);
    int r = str.length();

    glBegin(GL_LINES);

    glShadeModel(GL_FLAT);
    int i = 15;
    int d = 0;
    int y1 = -10;
    while (i <= r * 4 + 11)
    {
        glColor3f(0.0, 0.0, 0.0);

        glVertex2f(i, 0);
        glVertex2f(i + 4, 0);

        glColor3f(0.5, 0.0, 0.0);
        if (str[d] == '0')
        {
            glVertex2f(i, 0);
            glVertex2f(i + 4, 0);
        }
        else
        {
            y1 = -y1;
            glVertex2f(i, 0);
            glVertex2f(i, y1);
            glVertex2f(i, y1);
            glVertex2f(i + 4, y1);
            glVertex2f(i + 4, y1);
            glVertex2f(i + 4, 0);
        }

        i = i + 4;
        d++;
    }

    glColor3f(0.0, 0.0, 0.0);
    glVertex2f(i, 0);
    glVertex2f(i + 4, 0);

    glEnd();

    Notation();

    glFlush();
}

void B8ZS()
{
    LCS(8);
    SetupOfGraph("B8ZS", 95);
    int r = str.length();

    glBegin(GL_LINES);

    glShadeModel(GL_FLAT);
    int i = 15;
    int d = 0;
    int y1 = -10;
    int prevl = 0;
    while (i <= r * 4 + 11)
    {
        glColor3f(0.0, 0.0, 0.0);

        glVertex2f(i, 0);
        glVertex2f(i + 4, 0);

        glColor3f(0.5, 0.0, 0.0);
        if (ar.find(d) != ar.end())
        {
            glColor3f(0.0, 0.0, 0.0);
            glVertex2f(i, 0);
            glVertex2f(i + 32, 0);
            //000
            glColor3f(0.5, 0.0, 0.0);
            glVertex2f(i, 0);
            glVertex2f(i + 12, 0);
            if (prevl % 2 == 0)
            {
                //V
                glVertex2f(i + 12, 0);
                glVertex2f(i + 12, -10);
                glVertex2f(i + 12, -10);
                glVertex2f(i + 16, -10);
                glVertex2f(i + 16, -10);
                glVertex2f(i + 16, 0);
                //B
                glVertex2f(i + 16, 0);
                glVertex2f(i + 16, 10);
                glVertex2f(i + 16, 10);
                glVertex2f(i + 20, 10);
                glVertex2f(i + 20, 10);
                glVertex2f(i + 20, 0);
                //0
                glVertex2f(i + 20, 0);
                glVertex2f(i + 24, 0);
                //V
                glVertex2f(i + 24, 0);
                glVertex2f(i + 24, 10);
                glVertex2f(i + 24, 10);
                glVertex2f(i + 28, 10);
                glVertex2f(i + 28, 10);
                glVertex2f(i + 28, 0);
                //B
                glVertex2f(i + 28, 0);
                glVertex2f(i + 28, -10);
                glVertex2f(i + 28, -10);
                glVertex2f(i + 32, -10);
                glVertex2f(i + 32, -10);
                glVertex2f(i + 32, 0);
            }
            else
            {
                //V
                glVertex2f(i + 12, 0);
                glVertex2f(i + 12, 10);
                glVertex2f(i + 12, 10);
                glVertex2f(i + 16, 10);
                glVertex2f(i + 16, 10);
                glVertex2f(i + 16, 0);
                //B
                glVertex2f(i + 16, 0);
                glVertex2f(i + 16, -10);
                glVertex2f(i + 16, -10);
                glVertex2f(i + 20, -10);
                glVertex2f(i + 20, -10);
                glVertex2f(i + 20, 0);
                //0
                glVertex2f(i + 20, 0);
                glVertex2f(i + 24, 0);
                //V
                glVertex2f(i + 24, 0);
                glVertex2f(i + 24, -10);
                glVertex2f(i + 24, -10);
                glVertex2f(i + 28, -10);
                glVertex2f(i + 28, -10);
                glVertex2f(i + 28, 0);
                //B
                glVertex2f(i + 28, 0);
                glVertex2f(i + 28, 10);
                glVertex2f(i + 28, 10);
                glVertex2f(i + 32, 10);
                glVertex2f(i + 32, 10);
                glVertex2f(i + 32, 0);
            }
            d = d + 8;
            i = i + 32;
        }
        else
        {
            if (str[d] == '0')
            {
                glVertex2f(i, 0);
                glVertex2f(i + 4, 0);
            }
            else
            {
                y1 = -y1;
                glVertex2f(i, 0);
                glVertex2f(i, y1);
                glVertex2f(i, y1);
                glVertex2f(i + 4, y1);
                glVertex2f(i + 4, y1);
                glVertex2f(i + 4, 0);
                prevl++;
            }

            i = i + 4;
            d++;
        }
    }

    glColor3f(0.0, 0.0, 0.0);
    glVertex2f(i, 0);
    glVertex2f(i + 4, 0);

    glEnd();

    Notation();

    glFlush();
}

void HDB3()
{
    LCS(4);
    SetupOfGraph("HDB3", 95);
    int r = str.length();

    glBegin(GL_LINES);

    glShadeModel(GL_FLAT);
    int i = 15;
    int d = 0;
    int y1 = -10;
    int prevStatus = 0;
    while (i <= r * 4 + 11)
    {
        glColor3f(0.0, 0.0, 0.0);

        glVertex2f(i, 0);
        glVertex2f(i + 4, 0);

        glColor3f(0.5, 0.0, 0.0);
        if (ar.find(d) != ar.end())
        {

            glColor3f(0.0, 0.0, 0.0);
            glVertex2f(i, 0);
            glVertex2f(i + 16, 0);

            glColor3f(0.5, 0.0, 0.0);
            if (prevStatus % 2 == 0)
            {
                //B
                y1 = -y1;
                glVertex2f(i, 0);
                glVertex2f(i, y1);
                glVertex2f(i, y1);
                glVertex2f(i + 4, y1);
                glVertex2f(i + 4, y1);
                glVertex2f(i + 4, 0);
                //0
                glVertex2f(i + 4, 0);
                glVertex2f(i + 8, 0);
                //0
                glVertex2f(i + 8, 0);
                glVertex2f(i + 12, 0);
                //V
                glVertex2f(i + 12, 0);
                glVertex2f(i + 12, y1);
                glVertex2f(i + 12, y1);
                glVertex2f(i + 16, y1);
                glVertex2f(i + 16, y1);
                glVertex2f(i + 16, 0);
            }
            else
            {
                //0
                glVertex2f(i, 0);
                glVertex2f(i + 4, 0);
                //0
                glVertex2f(i + 4, 0);

                glVertex2f(i + 8, 0);
                //0
                glVertex2f(i + 8, 0);
                glVertex2f(i + 12, 0);
                //V
                glVertex2f(i + 12, 0);
                glVertex2f(i + 12, y1);
                glVertex2f(i + 12, y1);
                glVertex2f(i + 16, y1);
                glVertex2f(i + 16, y1);
                glVertex2f(i + 16, 0);
            }
            d = d + 4;
            i = i + 16;
        }
        else
        {
            if (str[d] == '0')
            {
                glVertex2f(i, 0);
                glVertex2f(i + 4, 0);
            }
            else
            {
                y1 = -y1;
                glVertex2f(i, 0);
                glVertex2f(i, y1);
                glVertex2f(i, y1);
                glVertex2f(i + 4, y1);
                glVertex2f(i + 4, y1);
                glVertex2f(i + 4, 0);
                prevStatus++;
            }

            i = i + 4;
            d++;
        }
    }

    glColor3f(0.0, 0.0, 0.0);
    glVertex2f(i, 0);
    glVertex2f(i + 4, 0);

    glEnd();

    Notation();

    glFlush();
}

int main(int argc, char **argv)
{
    int n;
    cout << "Enter 1 for encoding schemes and 0 for exit: ";
    cin >> n;
    while (n)
    {
        str = "";
        system("cls");
        cout << "Enter your choice to perform various encoding schemes and else to exit : \n1.NRZ-L   2.NRZ-I    3.Manchester    4.Differential Manchester     5.AMI\n";
        int ch;
        cin >> ch;
        if(ch>5 || ch<1)
            break;
        cout << "Enter the type of binary sequence needed \n1.random data      2.data with some fixed subsequence\n";
        int flag;
        cin >> flag;
        int l;
        system("cls");
        cout << "Length of string: ";
        cin >> l;
        if (flag == 1)
            generateRandomString(l);
        if (flag == 2)
            generateStringCsubseq(l);

        cout << "Generated String: " << str;
        findLongestPalindromicString();
        cout << "Enter 1 to see digital output else to continue: ";
        int t;
        cin >> t;

        if (t == 1)
        {
            windowsInitialisation(argc, argv);
            if (ch == 1)
                glutDisplayFunc(NRZL);
            else if (ch == 2)
                glutDisplayFunc(NRZI);
            else if (ch == 3)
                glutDisplayFunc(Manchester);
            else if (ch == 4)
                glutDisplayFunc(DManchester);
            else if (ch == 5)
            {
                    glutDisplayFunc(AMI);

                    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE,
                    GLUT_ACTION_GLUTMAINLOOP_RETURNS);

                    glutReshapeFunc(reshape);
                    init();
                    glutMainLoop();

                    cout << "Would you like to implement scrambling? (Y/N): ";
                    char c;
                    cin >> c;
                    if(c=='Y' || c=='y')
                    {
                    int h;
                    cout << "Enter your choice for type of scrambling else for exit\n1.B8ZS    2.HDB3\n";
                    cin >> h;
                    windowsInitialisation(argc, argv);
                    if (h == 1)
                        glutDisplayFunc(B8ZS);
                    else if (h == 2)
                        glutDisplayFunc(HDB3);
                        else
                            break;
                    }
                    else
                        break;
                }

            glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE,
              GLUT_ACTION_GLUTMAINLOOP_RETURNS);

            glutReshapeFunc(reshape);
            init();
            glutMainLoop();
        }
    }
}
