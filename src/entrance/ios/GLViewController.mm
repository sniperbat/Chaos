#import <QuartzCore/QuartzCore.h>
#import "GLViewController.h"
#import "EAGLView.h"
#include "chaos/Chaos.h"

//--------------------------------------------------------------------------------------------------
void makeChaosTouch( Chaos::ChsTouch & chsTouch, NSSet * touches, UIView * view );
void makeChaosTouch( Chaos::ChsTouch & chsTouch, NSSet * touches, UIView * view ){
  chsTouch.numberOfTouches = [touches count];
  UITouch * touch = [touches anyObject];
  CGPoint location = [touch locationInView:view];
  chsTouch.location.x = location.x;
  chsTouch.location.y = location.y;
  location = [touch previousLocationInView:view];
  chsTouch.previousLocation.x = location.x;
  chsTouch.previousLocation.y = location.y;
}

//--------------------------------------------------------------------------------------------------
void makeChaosTouch( Chaos::ChsTouch & chsTouch, UIGestureRecognizer * recognizer, UIView * view );
void makeChaosTouch( Chaos::ChsTouch & touch, UIGestureRecognizer * recognizer, UIView * view ){
  touch.state = recognizer.state;
  touch.numberOfTouches = recognizer.numberOfTouches;
  CGPoint gesturePoint = [recognizer locationInView:view];
  touch.location.x = gesturePoint.x;
  touch.location.y = gesturePoint.y;
}

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
-( void ) update {
	engine->run();
}

//--------------------------------------------------------------------------------------------------
-( void ) setDisplayLinkToPresent {
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
-( void ) resetDisplayLink {
	if( self.isPresenting ){
		[self.displayLink invalidate];
    	self.displayLink = nil;
    	self.isPresenting = FALSE;
	}
}

//--------------------------------------------------------------------------------------------------
-( void ) didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Release any cached data, images, etc that aren't in use.
}

//--------------------------------------------------------------------------------------------------
#pragma mark - View lifecycle
//--------------------------------------------------------------------------------------------------

-( void ) viewDidLoad {
	[super viewDidLoad];
	
	//frameInterval must greater then 0, 1 = 60fps, 2 = 30fps etc...
	self.frameInterval = 1;
	Chaos::ChsRenderSystemIOSSetTargetGLLayer( ( CAEAGLLayer * )self.view.layer );
	engine = Chaos::ChsEngine::sharedInstance();
  [self initGestures];
}

//--------------------------------------------------------------------------------------------------
-( void ) viewDidUnload {
	[super viewDidUnload];
	engine->shutdown();
}

//--------------------------------------------------------------------------------------------------
-( void ) viewWillAppear : ( BOOL )animated {
	[super viewWillAppear:animated];
}

//--------------------------------------------------------------------------------------------------
-( void ) viewDidAppear : ( BOOL )animated {
    [super viewDidAppear:animated];
	//at this time, the view`s frame was set,
	//renderer will get the last render frame buffer size, as orientation init
	engine->start();
	[self setDisplayLinkToPresent];
}

//--------------------------------------------------------------------------------------------------
-( void ) viewWillDisappear : ( BOOL )animated {
	[super viewWillDisappear:animated];
	[self resetDisplayLink];
}

//--------------------------------------------------------------------------------------------------
-( void ) viewDidDisappear : ( BOOL )animated {
	[super viewDidDisappear:animated];
}

//--------------------------------------------------------------------------------------------------
-( void ) initGestures {
  //pinch
  UIPinchGestureRecognizer * pinch = [[UIPinchGestureRecognizer alloc] initWithTarget:self 
                                                                               action:@selector(doPinch:)];
  pinch.cancelsTouchesInView = NO;
  pinch.delaysTouchesEnded = NO;
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
      tap.cancelsTouchesInView = NO;
      tap.delaysTouchesEnded = NO;
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
      swipe.cancelsTouchesInView = NO;
      swipe.delaysTouchesEnded = NO;
      [self.view addGestureRecognizer:swipe];
    }
  }
  
  //longpress 1 ~ 2 fingers
  static const int LONGPRESS_TOUCH_COUNT = 2;
  for( int numberOfTouchesRequired = 0; numberOfTouchesRequired<LONGPRESS_TOUCH_COUNT;numberOfTouchesRequired++){
    UILongPressGestureRecognizer * longPress = [[UILongPressGestureRecognizer alloc] initWithTarget:self
                                                                                             action:@selector(doLongPress:)];
    longPress.numberOfTouchesRequired = numberOfTouchesRequired+1;
    longPress.cancelsTouchesInView = NO;
    longPress.delaysTouchesEnded = NO;
    [self.view addGestureRecognizer:longPress];
  }
}

//--------------------------------------------------------------------------------------------------
#pragma mark - View touch event
//--------------------------------------------------------------------------------------------------
-( void ) touchesBegan:(NSSet *)touches
             withEvent:(UIEvent *)event {
  Chaos::ChsTouch chsTouch;
  makeChaosTouch( chsTouch, touches, self.view );
  chsTouch.state = Chaos::CHS_TOUCH_STATE_BEGAN;
  Chaos::ChsTouchEmitter::sharedInstance()->handleTouches( Chaos::CHS_TOUCH_TYPE_BEGAN, chsTouch );
}

//--------------------------------------------------------------------------------------------------
-( void ) touchesMoved:(NSSet *)touches 
             withEvent:(UIEvent *)event {
  Chaos::ChsTouch chsTouch;
  makeChaosTouch( chsTouch, touches, self.view );
  chsTouch.state = Chaos::CHS_TOUCH_STATE_CHANGED;
  Chaos::ChsTouchEmitter::sharedInstance()->handleTouches( Chaos::CHS_TOUCH_TYPE_CHANGED, chsTouch );
}

//--------------------------------------------------------------------------------------------------
-( void ) touchesEnded:(NSSet *)touches
             withEvent:(UIEvent *)event {
  Chaos::ChsTouch chsTouch;
  makeChaosTouch( chsTouch, touches, self.view );
  chsTouch.state = Chaos::CHS_TOUCH_STATE_ENDED;
  Chaos::ChsTouchEmitter::sharedInstance()->handleTouches( Chaos::CHS_TOUCH_TYPE_ENDED, chsTouch );
}

//--------------------------------------------------------------------------------------------------
-( void ) touchesCancelled:(NSSet *)touches
                 withEvent:(UIEvent *)event {
  Chaos::ChsTouch chsTouch;
  makeChaosTouch( chsTouch, touches, self.view );
  chsTouch.state = Chaos::CHS_TOUCH_STATE_CANCELLED;
  Chaos::ChsTouchEmitter::sharedInstance()->handleTouches( Chaos::CHS_TOUCH_TYPE_CANCELLED, chsTouch );
}

//--------------------------------------------------------------------------------------------------
-( void ) doPinch:(UIPinchGestureRecognizer *)recognizer {
  Chaos::ChsPinchTouch touch;
  makeChaosTouch( touch, recognizer, self.view );
  touch.scale = recognizer.scale;
  touch.velocity = recognizer.velocity;
  Chaos::ChsTouchEmitter::sharedInstance()->handleTouches( Chaos::CHS_TOUCH_TYPE_PINCH, touch );
}

//--------------------------------------------------------------------------------------------------
-( void ) doTap:(UITapGestureRecognizer *)recognizer {
  Chaos::ChsTapTouch touch;
  makeChaosTouch( touch, recognizer, self.view );
  touch.numberOfTaps = recognizer.numberOfTapsRequired;
  Chaos::ChsTouchEmitter::sharedInstance()->handleTouches( Chaos::CHS_TOUCH_TYPE_TAP, touch );
}

//--------------------------------------------------------------------------------------------------
-( void ) doSwipe:(UISwipeGestureRecognizer *)recognizer {
  Chaos::ChsSwipeTouch touch;
  makeChaosTouch( touch, recognizer, self.view );
  touch.direction = recognizer.direction;
  Chaos::ChsTouchEmitter::sharedInstance()->handleTouches( Chaos::CHS_TOUCH_TYPE_SWIPE, touch );
}

//--------------------------------------------------------------------------------------------------
-( void ) doLongPress:(UILongPressGestureRecognizer *)recognizer {
  Chaos::ChsLongPressTouch touch;
  makeChaosTouch( touch, recognizer, self.view );
  Chaos::ChsTouchEmitter::sharedInstance()->handleTouches( Chaos::CHS_TOUCH_TYPE_LONGPRESS, touch );
}

//--------------------------------------------------------------------------------------------------
#pragma mark - View Orientation
//--------------------------------------------------------------------------------------------------
-( BOOL ) shouldAutorotateToInterfaceOrientation : ( UIInterfaceOrientation )interfaceOrientation {
	return ( interfaceOrientation == UIInterfaceOrientationLandscapeLeft || 
			interfaceOrientation == UIInterfaceOrientationLandscapeRight );
}

//--------------------------------------------------------------------------------------------------
@end
