//
//  ViewController.m
//  repl
//
//  Created by Timm on 27.07.15.
//  Copyright (c) 2015 Timm Knape Softwaretechnik (http://www.kna-st.de). All rights reserved.
//

#import "ViewController.h"

#import "parser.h"
#import "fnprint.h"
#import "stream_handler_collector.h"

#import <sstream>

@implementation ViewController {
	State *_state;
    Parser *_parser;
    StreamHandlerCollector *_collector;
}

- (void)viewDidLoad {
    [super viewDidLoad];

    if (! _collector) { _collector = new StreamHandlerCollector(); }
    if (! _state) {
        _state = new State();
        _state->setName("root");
        dynamic_cast<FunctionPrint *>(_state->root()->as_dictionary()->get("print"))->setHandler(_collector);
        dynamic_cast<FunctionPrint *>(_state->root()->as_dictionary()->get("err-print"))->setHandler(_collector);
    }
    if (! _parser) {
        _collector->str(std::string());
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
        NSString *stream_string = [NSString stringWithUTF8String: _collector->str().c_str()];
        [self.sourceField insertText: stream_string replacementRange: NSMakeRange(self.sourceField.textStorage.string.length, 0)];
    }
}

- (void)setRepresentedObject:(id)representedObject {
    [super setRepresentedObject:representedObject];

    // Update the view, if already loaded.
}

- (void) dealloc {
    if (_parser) { delete _parser; _parser = nullptr; }
    if (_state) { delete _state; _state = nullptr; }
    if (_collector) { delete _collector; _collector = nullptr; }
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
            _collector->str(std::string());
            EPtr out = _state->eval(in);
            if (out) {
                std::ostringstream result; result << out;
                NSString *stream_string = [NSString stringWithUTF8String: _collector->str().c_str()];
                NSString *result_string = [NSString stringWithUTF8String: result.str().c_str()];
                NSString *replacement = [NSString stringWithFormat: @"\n%@%@\n", stream_string, result_string];
                [textView insertText: replacement replacementRange: affectedCharRange];
                return NO;
            }
        }
    }
    return YES;
}

@end
