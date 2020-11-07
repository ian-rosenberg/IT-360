#define SDL2_MAIN_HANDLED
#define GL3_PROTOTYPES 1

#include <math.h>
#include <memory>
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>

//On Linux change these lines to <SDL2/... .h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_ttf.h>


#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>

using namespace std;

const float d_h = 0.015;
const float TIME_STEP = 0.5F;
const float MAX_FORCE = 0.1F;
const float MAX_SPEED = 1.5F;

float distance(float x1, float y1, float x2, float y2) {
	return sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
}

class Agent{
private:
	float			cx;
	float			cy;
	float			vx;
	float			vy;
	float			r;
	float			vxGoal;
	float			vyGoal;
	
public:
	Agent(){
		r = 5;

		cx = rand() % 1025;
		cy = rand() % 1025;

		vx = (float(rand() * 2 + 0.5) * float(rand() < 0.5 ? 5 : -5));
		vy = (float(rand() * 2 + 0.5) * float(rand() < 0.5 ? 5 : -5));

		vxGoal = (float(rand() * 2 + 0.5) * float(rand() < 0.5 ? 5 : -5));
		vyGoal = (float(rand() * 2 + 0.5) * float(rand() < 0.5 ? 5 : -5));
	}

	float GetRadius() {
		return r;
	}

	float GetPositionX() {
		return cx;
	}
	
	float GetPositionY() {
		return cy;
	}

	float GetVelocityX() {
		return vx;
	}
	
	float GetVelocityY() {
		return vy;
	}


	void Update(vector<Agent*> *agents, int agentCount, int agentIndex) {
		if (cx < -r)
		{
			cx = 1024.0+r;
		}
		else if (cx > 1024.0 + r)
		{
			cx = 0.0-r;
		}
		if (cy < -r)
		{
			cy = 1024.0+r;
		}
		else if (cy > 1024.0 + r)
		{
			cy = 0.0-r;
		}

		float vX = vx;
		float vY = vy;
		float zeta = 1.0023;
		float f_goal_x = (vxGoal - vx) / zeta;
		float f_goal_y = (vyGoal - vy) / zeta;
		float f_avoid_x = 0;
		float f_avoid_y = 0;
		float f_avoid_ctr = 0;
		float interacting_agents_cntr = 0;

		for (int j = 0; j < agentCount; j++){
			if (agentIndex == j){ 
				continue; 
			}

			float dist = distance((*agents)[agentIndex]->cx, (*agents)[agentIndex]->cy, (*agents)[j]->cx, (*agents)[j]->cy);

			if (dist > 0 && dist < d_h){
				float d_ab = __max(dist - r, 0.001);
				float k = __max(d_h - d_ab, 0);
				float x_ab = ((*agents)[agentIndex]->cx - (*agents)[j]->cx) / dist;
				float y_ab = ((*agents)[agentIndex]->cy - (*agents)[j]->cy) / dist;
				interacting_agents_cntr += 1;
				f_avoid_x += k * x_ab / d_ab;
				f_avoid_y += k * y_ab / d_ab;
				f_avoid_ctr += 1;
			}
		}

		if (f_avoid_ctr > 0) {
			f_avoid_x = f_avoid_x / f_avoid_ctr;
			f_avoid_y = f_avoid_y / f_avoid_ctr;
		}

		float force_sum_x = f_goal_x + f_avoid_x;
		float force_sum_y = f_goal_y + f_avoid_y;

		float f_avoid_mag = sqrt(force_sum_x*force_sum_x + force_sum_y * force_sum_y);

		if (f_avoid_mag > MAX_FORCE){
			force_sum_x = MAX_FORCE * force_sum_x / f_avoid_mag;
			force_sum_y = MAX_FORCE * force_sum_y / f_avoid_mag;
		}

		vX += TIME_STEP * force_sum_x;
		vY += TIME_STEP * force_sum_y;
		float speed = sqrt(vX*vX + vY * vY);
		if (speed > MAX_SPEED)
		{
			vX = MAX_SPEED * vX / speed;
			vY = MAX_SPEED * vY / speed;
		}

		vx = vX;
		vy = vY;
		cx += TIME_STEP * vX;
		cy += TIME_STEP * vY;
	}

	void Draw(){

        glPushMatrix();
		glColor3f(0.0, 0.0, 0.0);
		glBegin(GL_TRIANGLES);

		glVertex3f(cx, cy, 0.0);
		for (int theta = 0; theta < 37; theta++){
			glVertex3f(cx, cy, 0.0);

			float rads = M_PI * (theta * 10) / 180;

			float x = cx + r * cos(rads);
			float y = cy + r * sin(rads);
			
			glVertex3f(x, y, 0.0);

			if (theta == 36){
				rads = 0;

				float x = cx + r * cos(rads);
				float y = cy + r * sin(rads);

				glVertex3f(x, y, 0.0);
			}
			else{
				rads = M_PI * (theta * 10) / 180;

				float x = cx + r * cos(rads);
				float y = cy + r * sin(rads);

				glVertex3f(x, y, 0.0);
			}
		}
		glEnd();
		glPopMatrix();
	}
};

class Bucket {
private:
	int				id;

	Bucket			*next;
	Bucket			*prev;

	vector<Agent*>	agents;

public:
	Bucket() {
		id = 0;

		next = NULL;
		prev = NULL;

		agents = vector<Agent*>();
	}

	Bucket(int i) {
		id = i;

		prev = NULL;
		next = NULL;

		agents = vector<Agent*>();
	}

	Bucket(int i, Bucket *p) {
		id = i;

		prev = p;
		next = NULL;

		agents = vector<Agent*>();
	}

	~Bucket() {
		int i = int(agents.size()) - 1;
		for (; i >= 0; i--) {
			agents.pop_back();
		}
	}

	void SetNextPtr(Bucket *nextBucket) {
		next = nextBucket;
	}

	void SetPrevPtr(Bucket *nextBucket) {
		prev = nextBucket;
	}

	int GetId() {
		return id;
	}

	void AddAgent(Agent *agent) {
		agents.push_back(agent);
	}

	vector<Agent*>* GetAgents() {
		return &agents;
	}
};

class SpatialHash {
private:
	int				cellSize;
	int				cols;
	int				rows;
	int				sceneHeight;
	int				sceneWidth;
	
	vector<Bucket*> buckets;

public:

	SpatialHash() {
		cellSize = 0;
		cols = 0;
		rows = 0;
		sceneWidth = 0;
		sceneHeight = 0;
		buckets = vector<Bucket*>();
	}

	SpatialHash(int sceneWidth, int sceneHeight, int size) {
		buckets = vector<Bucket*>();
		
		Setup(sceneWidth, sceneHeight, size);
	}

	~SpatialHash(){
		int i = int(buckets.size()) - 1;
		for (; i >= 0; i--) {
			vector<Agent*> *agentsInBucket = buckets[i]->GetAgents();
			for (int j = agentsInBucket->size(); j >= 0; j--) {
				(*agentsInBucket).pop_back();
			}
		}
	}

	void Setup(int scenewidth, int sceneheight, int cellsize){
		cols = scenewidth / cellsize;
		rows = sceneheight / cellsize;
		cellSize = cellsize;
		sceneHeight = sceneheight;
		sceneWidth = scenewidth;
		Bucket *current = NULL;
		Bucket *prev = NULL;
		int i = 0;

		for (; i < cols*rows; i++) {
			prev = current;
			current = new Bucket(i, NULL);

			buckets.push_back(current);

			if (prev != NULL) {
				current->SetPrevPtr(prev);
				prev->SetNextPtr(current);
			}
		}

		printf("There are %i buckets", buckets.size());
	}

	void ClearBuckets() {
		for (int i = 0; i < int(buckets.size()); i++)
		{
			vector<Agent*> *agents = buckets[i]->GetAgents();

			agents->clear();
		}

		buckets.clear();
	}

	vector<Bucket*>* GetNearby(Agent *agent) {
		vector<Bucket*> *nearby = new vector<Bucket*>();
		vector<Bucket*> *b = GetBucketsForAgent(agent);
		for (int i = 0; i < int(b->size()); i++) {
			nearby->push_back((*b)[i]);
		}

		return nearby;
	}

	vector<Bucket*>* GetBucketsForAgent(Agent *agent){
		vector<Bucket*> *bucketsAgentIsIn = new vector<Bucket*>();

		int minx = agent->GetPositionX();
		int miny = agent->GetPositionY();

		int maxx = agent->GetRadius() + minx;
		int maxy = agent->GetRadius() + miny;

		float width = sceneWidth / cellSize;
		//TopLeft
		AddBucket(minx, miny, width, bucketsAgentIsIn);
		//TopRight
		AddBucket(maxx, miny, width, bucketsAgentIsIn);
		//BottomRight
		AddBucket(maxx, maxy, width, bucketsAgentIsIn);
		//BottomLeft
		AddBucket(minx, maxy, width, bucketsAgentIsIn);

		return bucketsAgentIsIn;
	}

	void AddBucket(int pX, int pY, float width, vector<Bucket*> *bucketList)
	{
		int cellPosition = (int)(
			(floor(pX / cellSize)) +
			(floor(pY / cellSize)) *
			width
			);
		Bucket* usedBucket = GetBucketById(cellPosition);
		Uint8 flag = 0;

		if (usedBucket == NULL) {
			if (buckets.size() == 0) {
				usedBucket = new Bucket(cellPosition);
			}
			else {

				for (int i = 0; i < (*bucketList).size(); i++) {
					if ((*bucketList)[i]->GetId() == cellPosition) {
						flag = 1;
					}

					if (flag == 0) {
						usedBucket = new Bucket(cellPosition, (*bucketList)[int(bucketList->size()) - 1]);

						bucketList->push_back(usedBucket);
					}
				}
			}
		}
	}

	void RegisterAgent(Agent *agent)
	{
		vector<Bucket*> *cellIds = GetBucketsForAgent(agent);
		float width = sceneWidth / cellSize;
		
		if (cellIds == NULL) {
			AddBucket(agent->GetPositionX(), agent->GetPositionY(), width, &buckets);
		}
		else {
			for (int item = 0; item < int(cellIds->size()); item++)
			{
				(*cellIds)[item]->AddAgent(agent);
				fprintf(stdout, "Adding agent to bucket with id %i \n", (*cellIds)[item]->GetId());
			}
		}
	}

	Bucket* GetBucketById(int id) {
		for (int i = 0; i < int(buckets.size()); i++)
		{
			if (buckets[i]->GetId() == id)
				return buckets[i];
		}

		return NULL;
	}

	void UpdateAgents() {
		int bucketSize = int(buckets.size());

		for (int i = 0; i < bucketSize; i++)
		{
			vector<Agent*> *agents = buckets[i]->GetAgents();
			int agentCount = int(agents->size());

			for (int j = 0; j < agentCount; j++) {
				(*agents)[j]->Update(agents, agentCount, j);
			}
		}
	}

	void DrawAgents() {
		for (int i = 0; i < int(buckets.size()); i++)
		{
			vector<Agent*> *agents = buckets[i]->GetAgents();

			for (int j = 0; j < int((*agents).size()); j++) {
				(*agents)[j]->Draw();
			}
		}
	}
};

class Window{
private:
	SDL_Window			*window;
	SDL_Renderer		*renderer;
	SDL_Texture			*tex;
	SDL_Surface			*surface;
	SDL_Surface			*tempSurface;
	SDL_GLContext		context;

	double				framerate;
	SDL_Texture			*fpsTex;
	TTF_Font			*font;

	Uint32				prevTime, curTime, frameDelay;
	int					width, height;


public:
	Window()
	{
		window = NULL;
		renderer = NULL;
		tex = NULL;
		surface = new SDL_Surface();
		tempSurface = new SDL_Surface();
		context = NULL;
		width = 1024;
		height = 1024;
		prevTime = 0;
		curTime = 0;
		frameDelay = 16;
	}
	
	void Window_Init(char **args)
	{
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		}
		else
		{	//Create window
			width = 1024;
			height = 1024;

			window = SDL_CreateWindow("Exercise 3", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

			if (strcmp(args[1], "-fps") == 0)
			{
				if (TTF_Init() < 0)
				{
					fprintf(stdout, "Failed to init SDL2_TTF\n");
				}

				fprintf(stdout, "SDL2_TTF initialized!\n");

				font = TTF_OpenFont("impact.ttf", 24);
			}

			if (window == NULL)
			{
				printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			}
			else
			{
				renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

				SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
				
				surface = SDL_GetWindowSurface(window);

				context = SDL_GL_CreateContext(window);
				
				if (context != NULL)
				{
					initGL();
					
					SetOpenGLAttributes();
					
					SDL_GL_SetSwapInterval(1);

					SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0xFF, 0xFF, 0xFF));
					SDL_UpdateWindowSurface(window);

					srand(SDL_GetTicks());
				}
				else {
					printf("SDL_OpenGL context is not valid!");
				}
			}
		}
	}
	
	~Window(){
		SDL_GL_DeleteContext(context);

		SDL_DestroyTexture(tex);

		SDL_DestroyTexture(fpsTex);
		
		SDL_DestroyWindow(window);
		
		SDL_Quit();
	}

	SDL_Renderer* GetRenderer() {
		return renderer;
	}

	int GetWidth() {
		return width;
	}

	int GetHeight() {
		return height;
	}

	bool initGL(){
		bool success = true;
		GLenum error = GL_NO_ERROR;

		//Initialize Projection Matrix
		glMatrixMode( GL_PROJECTION );
		glLoadIdentity();
		glOrtho(0.0, 1024.0, 0.0, 1024.0, 0.0, -1.0);
		
		//Check for error
		error = glGetError();
		if( error != GL_NO_ERROR )
		{
			printf( "Error initializing OpenGL! %s\n", error);
			success = false;
		}

		glMatrixMode( GL_MODELVIEW );
		glLoadIdentity();

		error = glGetError();
		if( error != GL_NO_ERROR )
		{
			printf( "Error initializing OpenGL! %s\n", error);
			success = false;
		}

		//Initialize clear color
		glClearColor( 0.f, 0.f, 0.f, 1.f );
		
		//Check for error
		error = glGetError();
		if( error != GL_NO_ERROR )
		{
			printf("Error initializing OpenGL! %s\n", error);
			success = false;
		}
		
		return success;
	}

	void NextFrame()
	{
		SDL_GL_SwapWindow(window);

		FrameDelay();
	}

	int nextpoweroftwo(int x)
	{
		double logbase2 = log(x) / log(2);
		return round(pow(2, ceil(logbase2)));
	}

	float GetFrameRate()
	{
		return framerate;
	}
	
	void SetOpenGLAttributes()
	{
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	}

	void FrameDelay()
	{
		Uint32 diff;
		prevTime = curTime;
		curTime = SDL_GetTicks();
		diff = (curTime - prevTime);
		if (diff < frameDelay)
		{
			SDL_Delay(frameDelay - diff);
		}

		framerate = 1000.0 / __max(SDL_GetTicks() - prevTime, 0.001);
	}
	void DrawFrameRateTexture() 
	{
		SDL_Rect rect = { 0,990,100,100 };
		SDL_Color color = { 0,255,0 };
		SDL_Surface *initial;
		SDL_Surface *intermediary;
		
		int w, h;
		GLuint texture;

		stringstream stream;
		stream << fixed << setprecision(2) << framerate;
		string s = stream.str();

		initial = TTF_RenderText_Blended(font, s.c_str(), color);
		if (initial == NULL)
			return;

		w = nextpoweroftwo(initial->w);
		h = nextpoweroftwo(initial->h);

		intermediary = SDL_CreateRGBSurface(0, w, h, 32,
			0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);

		SDL_BlitSurface(initial, 0, intermediary, 0);

		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, 4, w, h, 0, GL_BGRA,
			GL_UNSIGNED_BYTE, intermediary->pixels);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture);
		glColor3f(1.0f, 1.0f, 1.0f);

		glBegin(GL_QUADS);

		glTexCoord2f(0.0f, 1.0f);
		glVertex2f(rect.x, rect.y);
		glTexCoord2f(1.0f, 1.0f);
		glVertex2f(rect.x + w, rect.y);
		glTexCoord2f(1.0f, 0.0f);
		glVertex2f(rect.x + w, rect.y + h);
		glTexCoord2f(0.0f, 0.0f);
		glVertex2f(rect.x, rect.y + h);
		glEnd();

		glFinish();

		rect.w = initial->w;
		rect.h = initial->h;

		SDL_FreeSurface(initial);
		SDL_FreeSurface(intermediary);
		glDeleteTextures(1, &texture);
	}
};

void drawBackground(float w, float h){
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);

	glVertex3f(-w, -h, 0.0);
	glVertex3f(w, -h, 0.0);
	glVertex3f(w, h, 0.0);
	glVertex3f(-w, h, 0.0);

	glEnd();
	glPopMatrix();
}

int main(int argc, char **argv)
{
	Uint8 done = false;
	SDL_Event e;
	const Uint8 *keys;
	Window *win = new Window();
	int agentCount = 1 * floor(win->GetWidth() / 2);
	SpatialHash *sHash = new SpatialHash();
	vector<Agent*> agents;
	string pArgs[] = { "-favoid","-fps","-shash" };
	int flag = 0;

	win->Window_Init(argv);

	if (strcmp(argv[1], "-fps") == 0) {
		printf("\nfps flag set!\n");
		flag = 2;
	}
	else if (strcmp(argv[1], "-shash") == 0) {
		printf("\nshash flag set!\n");
		flag = 3;
		sHash->Setup(1024, 1024, 16);
	}
	else if (strcmp(argv[1], "-favoid") == 0) {
		printf("\nfavoid flag set!\n");
		flag = 1;
	}

	if (flag == 0) {
		printf("No arguments provided... closing program.");

		return 1;
	}

	for (int i = 0; i < agentCount; i++) {
		agents.push_back(new Agent());
	}

	SDL_ShowCursor(SDL_DISABLE);

	while (!done){
		glClear(GL_COLOR_BUFFER_BIT); 

		SDL_PumpEvents();

		keys = SDL_GetKeyboardState(NULL);


		if (flag < 3) {
			for (int i = 0; i < agentCount; i++) {
				agents[i]->Update(&agents, agentCount, i);
			}
		}
		else
		{
			sHash->ClearBuckets();

			sHash->Setup(1024, 1024, 16);
			
			for (int i = 0; i < agentCount; i++) {
				sHash->RegisterAgent(agents[i]);
			}

			sHash->UpdateAgents();
		}
		
		drawBackground(1024, 1024);

		if (flag < 3) {
			for (int i = 0; i < agentCount; i++) {
				agents[i]->Draw();
			}
		} 
		else{
			sHash->DrawAgents();
		}

		if(flag == 2)
			win->DrawFrameRateTexture();

		win->NextFrame();

		if (keys[SDL_SCANCODE_ESCAPE]) {
			done = true;
		}
	}

	return 0;
}