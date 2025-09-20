local engine = {
    -- is a pointer from Handler C++
    _handler = nil,
    state = nil
}

function engine.setHandler(handler)
    engine["_handler"] = handler
end

function engine.getWinWidth()
    return engine.cHandlerGetWinWidth(engine["_handler"])
end

function engine.getWinHeight()
    return engine.cHandlerGetWinHeight(engine["_handler"])
end

function engine.getKey(scancode)
    return engine.cHandlerGetKey(engine["_handler"], scancode)
end

return engine