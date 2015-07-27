//
//  ViewController.m
//  repl
//
//  Created by Timm on 27.07.15.
//  Copyright (c) 2015 Timm Knape Softwaretechnik (http://www.kna-st.de). All rights reserved.
//

#import "ViewController.h"

#import "parser.h"

#import <sstream>

@implementation ViewController {
	State *_state;
    Parser *_parser;
}

- (void)viewDidLoad {
    [super viewDidLoad];

    if (! _state) { _state = new State(); _state->setName("root"); }
    if (! _parser) {
        _parser = new Parser(_state);
        NSURL *url = [NSBundle.mainBundle URLForResource: @"system" withExtension: @"lsp"];
        NSString *system = [NSString stringWithContentsOfURL: url encoding: NSUTF8StringEncoding error: nil];
        const char *data = [system cStringUsingEncoding: NSUTF8StringEncoding];
        std::istringstream stream(data);
		for (;;) {
			EPtr in = _parser->parse(stream);
			if (!in) { break; }
			_state->eval(in);
		}
    }
}

- (void)setRepresentedObject:(id)representedObject {
    [super setRepresentedObject:representedObject];

    // Update the view, if already loaded.
}

- (void) dealloc {
    if (_parser) { delete _parser; _parser = NULL; }
    if (_state) { delete _state; _state = NULL; }
}

- (BOOL)textView:(NSTextView *)textView shouldChangeTextInRange:(NSRange)affectedCharRange replacementString:(NSString *)replacementString {
    if ([replacementString isEqualToString: @"\n"]) {
        NSRange lineStart = [textView.textStorage.string rangeOfString:@"\n" options:NSBackwardsSearch range:NSMakeRange(0, affectedCharRange.location)];
        NSUInteger start = 0;
        if (lineStart.length) {
            start = lineStart.location + lineStart.length;
        }
        NSString *line = [textView.textStorage.string substringWithRange:NSMakeRange(start, affectedCharRange.location - start)];
        std::istringstream stream([line cStringUsingEncoding: NSUTF8StringEncoding]);
        EPtr in = _parser->parse(stream);
        if (in) {
            EPtr out = _state->eval(in);
            if (out) {
                std::ostringstream result; result << out;
                NSString *result_string = [NSString stringWithUTF8String: result.str().c_str()];
                NSString *replacement = [NSString stringWithFormat: @"\n%@\n", result_string];
                [textView insertText: replacement replacementRange: affectedCharRange];
                return NO;
            }
        }
    }
    return YES;
}

@end
