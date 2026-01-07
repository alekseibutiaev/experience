#include <string>
#include <memory>
#include <fstream>
#include <iostream>
#include <stdexcept>

#include <v8/v8.h>
#include <v8/libplatform/libplatform.h>

//const char* script = "var s = 0; for(var i = 1; i < 100; i++) s += i; s;";

// Extracts a C string from a V8 Utf8Value.
const char* ToCString(const v8::String::Utf8Value& value) {
  return *value ? *value : "<string conversion failed>";
}

void ReportException(v8::Isolate* isolate, v8::TryCatch* try_catch) {
  v8::HandleScope handle_scope(isolate);
  v8::String::Utf8Value exception(isolate, try_catch->Exception());
  const char* exception_string = ToCString(exception);
  v8::Local<v8::Message> message = try_catch->Message();
  if (message.IsEmpty()) {
    // V8 didn't provide any extra information about this error; just
    // print the exception.
    fprintf(stderr, "%s\n", exception_string);
  }
  else {
    // Print (filename):(line number): (message).
    v8::String::Utf8Value filename(isolate,
      message->GetScriptOrigin().ResourceName());
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    const char* filename_string = ToCString(filename);
    int linenum = message->GetLineNumber(context).FromJust();
    fprintf(stderr, "%s:%i: %s\n", filename_string, linenum, exception_string);
    // Print line of source code.
    v8::String::Utf8Value sourceline(isolate, message->GetSourceLine(context).ToLocalChecked());
    const char* sourceline_string = ToCString(sourceline);
    fprintf(stderr, "%s\n", sourceline_string);
    // Print wavy underline (GetUnderline is deprecated).
    int start = message->GetStartColumn(context).FromJust();
    for (int i = 0; i < start; i++) {
      fprintf(stderr, " ");
    }
    int end = message->GetEndColumn(context).FromJust();
    for (int i = start; i < end; i++) {
      fprintf(stderr, "^");
    }
    fprintf(stderr, "\n");
    v8::Local<v8::Value> stack_trace_string;
    if (try_catch->StackTrace(context).ToLocal(&stack_trace_string) &&
        stack_trace_string->IsString() &&
        v8::Local<v8::String>::Cast(stack_trace_string)->Length() > 0) {
      v8::String::Utf8Value stack_trace(isolate, stack_trace_string);
      const char* stack_trace_string = ToCString(stack_trace);
      fprintf(stderr, "%s\n", stack_trace_string);
    }
  }
}

std::string execute(v8::Isolate* isolate, const std::string& script) {
  // Create a stack-allocated handle scope.
  v8::HandleScope handle_scope(isolate);
  v8::TryCatch try_catch(isolate);
  v8::Isolate::Scope isolate_scope(isolate);
  // Create a new context.
  v8::Local<v8::Context> context = v8::Context::New(isolate);
  // Enter the context for compiling and running the hello world script.
  v8::Context::Scope context_scope(context);
  {
    // Create a string containing the JavaScript source code.
    v8::Local<v8::String> source = v8::String::NewFromUtf8(isolate, script.c_str()).ToLocalChecked();
    // Compile the source code.
    v8::Local<v8::Script> script;
    if(!v8::Script::Compile(context, source).ToLocal(&script)) {
      // error compile
      ReportException(isolate, &try_catch);
      return "Error";
    }
    v8::Local<v8::Value> res;
    if(!script->Run(context).ToLocal(&res)) {
      // error compile
      ReportException(isolate, &try_catch);
      return "Error";
    }
    if(!res->IsUndefined()) {
      v8::String::Utf8Value str(isolate, res);
      return ToCString(str);
    }
  }
  return std::string("undefinded");
}

std::string load_script(const std::string& name) {
  std::ifstream ifs(name.c_str());
  if(ifs.good()) {
    std::size_t len = [&ifs](){ ifs.seekg(0, ifs.end); std::size_t v = ifs.tellg(); ifs.seekg(0, ifs.beg); return v;}();
    std::unique_ptr<char[]> buf(new char[len]);
    ifs.read(buf.get(), len);
    return std::string(buf.get(), len);
  }
  throw(std::runtime_error("can`t open file: " + name));
}

int main(int ac, char* av[]) {
  try {
    std::cout << __SCRIPT_NAME__ << std::endl;
    v8::V8::InitializeICUDefaultLocation(av[0]);
  //  v8::V8::InitializeExternalStartupDataFromFile("/opt/v8lib/share/snapshot_blob.bin");
    v8::V8::InitializeExternalStartupData("/opt/v8lib/share/");
  //  v8::V8::SetSnapshotDataBlob(&sd);
    std::unique_ptr<v8::Platform> platform = v8::platform::NewDefaultPlatform();
    v8::V8::InitializePlatform(platform.get());
    v8::V8::Initialize();
    v8::V8::SetFlagsFromCommandLine(&ac, av, true);
    v8::Isolate::CreateParams create_params;
    create_params.array_buffer_allocator =
        v8::ArrayBuffer::Allocator::NewDefaultAllocator();
    v8::Isolate* isolate = v8::Isolate::New(create_params);
    std::cout << execute(isolate, load_script(__SCRIPT_NAME__)) << std::endl;
    isolate->Dispose();
    v8::V8::Dispose();
    v8::V8::ShutdownPlatform();
    delete create_params.array_buffer_allocator;
    return 0;
  }
  catch(const std::exception& e) {
    std::cout << e.what() << std::endl;
  }
}
