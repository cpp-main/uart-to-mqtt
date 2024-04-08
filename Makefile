.PHONY: clean distclean

CXX = g++

TARGET = uart_to_mqtt 
OBJECTS = apps.o uart_to_mqtt.o mqtt.o uart.o

CXXFLAGS := -I$(HOME)/.tbox/include/ -DLOG_MODULE_ID='"uart2mqtt"'
LDFLAGS := -L$(HOME)/.tbox/lib/
LIBS := \
	-ltbox_main \
	-ltbox_terminal \
	-ltbox_network \
	-ltbox_mqtt \
	-ltbox_eventx \
	-ltbox_event \
	-ltbox_log \
	-ltbox_util \
	-ltbox_base \
	-lmosquitto \
	-lpthread \
	-ldl

$(TARGET) : $(OBJECTS)
	$(CXX) -o $@ $^ $(LDFLAGS) $(LIBS)

clean: 
	rm -f $(OBJECTS)

distclean: clean
	rm -r $(TARGET)
