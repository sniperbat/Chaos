#import <QuartzCore/QuartzCore.h>
#import "GLViewController.h"
#import "EAGLView.h"
#include "chaos/Chaos.h"

//--------------------------------------------------------------------------------------------------
@interface GLViewController(){
	Chaos::ChsEngine * engine;
}

@property ( strong, nonatomic ) CADisplayLink * displayLink;
@property ( nonatomic ) BOOL isPresenting;
@property ( nonatomic ) NSInteger frameInterval;

-(void) setDisplayLinkToPresent;
-(void) resetDisplayLink;

@end

//--------------------------------------------------------------------------------------------------
@implementation GLViewController

@synthesize displayLink = _displayLink;
@synthesize isPresenting = _isPresenting;
@synthesize frameInterval = _frameInterval;

//--------------------------------------------------------------------------------------------------
-( void )update
{
	engine->run();
}

//--------------------------------------------------------------------------------------------------
-( void )setDisplayLinkToPresent
{
	if ( !self.isPresenting ) {
		CADisplayLink * aDisplayLink = [[UIScreen mainScreen] displayLinkWithTarget: self
                                                                       selector: @selector( update )];
		[aDisplayLink setFrameInterval: self.frameInterval];
		[aDisplayLink addToRunLoop: [NSRunLoop currentRunLoop]
                       forMode: NSDefaultRunLoopMode];
		self.displayLink = aDisplayLink;
		self.isPresenting = TRUE;
	}
}

//--------------------------------------------------------------------------------------------------
-( void )resetDisplayLink
{
	if( self.isPresenting ){
		[self.displayLink invalidate];
    	self.displayLink = nil;
    	self.isPresenting = FALSE;
	}
}

//--------------------------------------------------------------------------------------------------
-( void )didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Release any cached data, images, etc that aren't in use.
}

//--------------------------------------------------------------------------------------------------
#pragma mark - View lifecycle
//--------------------------------------------------------------------------------------------------

-( void )viewDidLoad
{
	[super viewDidLoad];
	
	//frameInterval must greater then 0, 1 = 60fps, 2 = 30fps etc...
	self.frameInterval = 1;
	Chaos::ChsRenderSystemIOSSetTargetGLLayer( ( CAEAGLLayer * )self.view.layer );
	engine = Chaos::ChsEngine::sharedInstance();
  [self initGestures];
}

//--------------------------------------------------------------------------------------------------
-( void )viewDidUnload
{
	[super viewDidUnload];
	engine->shutdown();
}

//--------------------------------------------------------------------------------------------------
-( void )viewWillAppear : ( BOOL )animated
{
	[super viewWillAppear:animated];
}

//--------------------------------------------------------------------------------------------------
-( void )viewDidAppear : ( BOOL )animated
{
    [super viewDidAppear:animated];
	//at this time, the view`s frame was set,
	//renderer will get the last render frame buffer size, as orientation init
	engine->start();
	[self setDisplayLinkToPresent];
}

//--------------------------------------------------------------------------------------------------
-( void )viewWillDisappear : ( BOOL )animated
{
	[super viewWillDisappear:animated];
	[self resetDisplayLink];
}

//--------------------------------------------------------------------------------------------------
-( void )viewDidDisappear : ( BOOL )animated
{
	[super viewDidDisappear:animated];
}

//--------------------------------------------------------------------------------------------------
-( void )initGestures
{
  //pinch
  UIPinchGestureRecognizer * pinch = [[UIPinchGestureRecognizer alloc] initWithTarget:self 
                                                                               action:@selector(doPinch:)];
  [self.view addGestureRecognizer: pinch];
  
  //taps 1 ~ 3 fingers, 1 ~ 3 taps
  static const int TAPS_COUNT = 3;
  static const int TAP_TOUCH_COUNT = 3;
  UITapGestureRecognizer * taps[TAP_TOUCH_COUNT][TAPS_COUNT];
  for( int numberOfTouchesRequired=0;numberOfTouchesRequired<TAP_TOUCH_COUNT;numberOfTouchesRequired++){
    for( int numberOfTapsRequired=0;numberOfTapsRequired<TAPS_COUNT;numberOfTapsRequired++){
      UITapGestureRecognizer * tap = [[UITapGestureRecognizer alloc] initWithTarget:self
                                                                             action:@selector(doTap:)];
      taps[numberOfTouchesRequired][numberOfTapsRequired] = tap;
      if( numberOfTapsRequired > 0)
        [taps[numberOfTouchesRequired][numberOfTapsRequired-1] requireGestureRecognizerToFail:tap];
      tap.numberOfTapsRequired = numberOfTapsRequired+1;
      tap.numberOfTouchesRequired = numberOfTouchesRequired+1;
      [self.view addGestureRecognizer: tap];
    }
  }
  
  //swipe 1 ~ 2 fingers, 4 directions
  static const int SWIPE_TOUCH_COUNT = 2;
  static const int SWIPE_DIRECTION = 4;
  for( int numberOfTouchesRequired = 0; numberOfTouchesRequired<SWIPE_TOUCH_COUNT;numberOfTouchesRequired++){
    for( int direction = 0; direction< SWIPE_DIRECTION;direction++){
      UISwipeGestureRecognizer * swipe = [[UISwipeGestureRecognizer alloc] initWithTarget:self
                                                                                   action:@selector(doSwipe:)];
      swipe.numberOfTouchesRequired = numberOfTouchesRequired+1;
      swipe.direction = ( UISwipeGestureRecognizerDirection )(1<<direction);
      [self.view addGestureRecognizer:swipe];
    }
  }
  
  //longpress 1 ~ 2 fingers
  static const int LONGPRESS_TOUCH_COUNT = 2;
  for( int numberOfTouchesRequired = 0; numberOfTouchesRequired<LONGPRESS_TOUCH_COUNT;numberOfTouchesRequired++){
    UILongPressGestureRecognizer * longPress = [[UILongPressGestureRecognizer alloc] initWithTarget:self
                                                                                             action:@selector(doLongPress:)];
    longPress.numberOfTouchesRequired = numberOfTouchesRequired+1;
    [self.view addGestureRecognizer:longPress];
  }
}

//--------------------------------------------------------------------------------------------------
#pragma mark - View touch event
//--------------------------------------------------------------------------------------------------
-( void )touchesBegan:(NSSet *)touches
            withEvent:(UIEvent *)event
{
  Chaos::ChsTouchEmitter::sharedInstance()->onTouchesBegan();
}

//--------------------------------------------------------------------------------------------------
-( void )touchesMoved:(NSSet *)touches 
            withEvent:(UIEvent *)event
{
  Chaos::ChsTouchEmitter::sharedInstance()->onTouchesMove();
}

//--------------------------------------------------------------------------------------------------
-( void )touchesEnded:(NSSet *)touches
            withEvent:(UIEvent *)event
{
  Chaos::ChsTouchEmitter::sharedInstance()->onTouchesEnded();
}

//--------------------------------------------------------------------------------------------------
-( void )touchesCancelled:(NSSet *)touches
                withEvent:(UIEvent *)event
{
  Chaos::ChsTouchEmitter::sharedInstance()->onTouchesCancelled();
}

//--------------------------------------------------------------------------------------------------
-( void )doPinch:(UIPinchGestureRecognizer *)recognizer
{
  Chaos::ChsTouchEmitter::sharedInstance()->onPinch( recognizer.state, recognizer.scale, recognizer.velocity );
}

//--------------------------------------------------------------------------------------------------
-( void )doTap:(UITapGestureRecognizer *)recognizer
{
  CGPoint gesturePoint = [recognizer locationInView:self.view]; //get the first one of taps,
  Chaos::ChsPoint position = { gesturePoint.x, gesturePoint.y };
  Chaos::ChsTouchEmitter::sharedInstance()->onTap( recognizer.numberOfTapsRequired, recognizer.numberOfTouches, position );
}

//--------------------------------------------------------------------------------------------------
-( void )doSwipe:(UISwipeGestureRecognizer *)recognizer
{
  CGPoint gesturePoint = [recognizer locationInView:self.view];
  Chaos::ChsPoint position = { gesturePoint.x, gesturePoint.y };
  Chaos::ChsTouchEmitter::sharedInstance()->onSwipe( recognizer.direction, recognizer.numberOfTouches, position );
}

//--------------------------------------------------------------------------------------------------
-( void )doLongPress:(UILongPressGestureRecognizer *)recognizer
{
  CGPoint gesturePoint = [recognizer locationInView:self.view];
  Chaos::ChsPoint position = { gesturePoint.x, gesturePoint.y };
  Chaos::ChsTouchEmitter::sharedInstance()->onLongPress( recognizer.state, recognizer.numberOfTouches, position );
}

//--------------------------------------------------------------------------------------------------
#pragma mark - View Orientation
//--------------------------------------------------------------------------------------------------
-( BOOL )shouldAutorotateToInterfaceOrientation : ( UIInterfaceOrientation )interfaceOrientation
{
	return ( interfaceOrientation == UIInterfaceOrientationLandscapeLeft || 
			interfaceOrientation == UIInterfaceOrientationLandscapeRight );
}

//--------------------------------------------------------------------------------------------------
@end
