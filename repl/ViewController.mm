//
//  ViewController.m
//  repl
//
//  Created by Timm on 27.07.15.
//  Copyright (c) 2015 Timm Knape Softwaretechnik (http://www.kna-st.de). All rights reserved.
//

#import "ViewController.h"

#import "parser.h"
#import "fnimport.h"
#import "fnprint.h"
#import "stream_handler_collector.h"
#import "import_handler_bundle.h"

#import <sstream>

@implementation ViewController {
	State *_state;
    Parser *_parser;
    NSMutableAttributedString *_buffer;
}

- (void)viewDidLoad {
    [super viewDidLoad];

    self.sourceField.automaticQuoteSubstitutionEnabled = NO;
    self.sourceField.automaticDashSubstitutionEnabled = NO;
    self.sourceField.automaticTextReplacementEnabled = NO;
    
    if (! _buffer) { _buffer = [NSMutableAttributedString new]; }
    if (! _state) {
        _state = new State();
        _state->setName("root");
        Dictionary *dict = _state->root()->as_dictionary();
        auto errCollector = new StreamHandlerCollector(_buffer, [NSColor redColor]);
        auto outCollector = new StreamHandlerCollector(_buffer, [NSColor grayColor]);
        dynamic_cast<FunctionPrint *>(dict->get("print"))->setHandler(outCollector);
        dynamic_cast<FunctionPrint *>(dict->get("err-print"))->setHandler(errCollector);
        dynamic_cast<FunctionImport *>(dict->get("import"))->setHandler(new ImportHandlerBundle());
    }
    if (! _parser) {
        [_buffer setAttributedString: [NSAttributedString new]];
        _parser = new Parser(_state);
        Dictionary *dict = _state->root()->as_dictionary();
        EPtr res = dynamic_cast<FunctionImport *>(dict->get("import"))->import("system.lsp", *_state);
        [_buffer appendAttributedString: [NSAttributedString.alloc initWithString: @"\n"]];
        [self.sourceField insertText: _buffer replacementRange: NSMakeRange(self.sourceField.textStorage.string.length, 0)];
    }
}

- (void) dealloc {
    if (_parser) { delete _parser; _parser = nullptr; }
    if (_state) { delete _state; _state = nullptr; }
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
        [_buffer setAttributedString: [NSAttributedString new]];
            EPtr out = _state->eval(in);
            if (out) {
                std::ostringstream result; result << out;
                NSMutableAttributedString *formatted = [[NSMutableAttributedString alloc] initWithString: @"\n"];
                [formatted appendAttributedString: _buffer];
                NSString *result_string = [NSString stringWithUTF8String: result.str().c_str()];
                [formatted appendAttributedString: [NSAttributedString.alloc initWithString: result_string attributes: @{
                    NSForegroundColorAttributeName: NSColor.whiteColor
                }]];
                [formatted appendAttributedString: [NSAttributedString.alloc initWithString: @"\n"]];
                [textView insertText: formatted replacementRange: affectedCharRange];
                return NO;
            }
        }
    }
    return YES;
}

@end
