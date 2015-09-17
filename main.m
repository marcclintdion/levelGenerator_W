#if helios
#import <UIKit/UIKit.h>
#else
#import <Cocoa/Cocoa.h>
#endif


int main(int argc, char *argv[])
{
	int retVal = 1;

    NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
    retVal = UIApplicationMain(argc, argv, nil, nil);
    [pool release];

	
    return retVal;
}


















