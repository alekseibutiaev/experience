TARGET = pcl6.a

OBJS = CDataType.o CAttribute.o CEmbedType.o CreateAttribute.o COperator.o \
	CNullAttributeList.o CBeginSession.o \
	COpenDataSource.o CBeginPage.o CSetPageOrigin.o CSetPageScale.o \
	CSetClipMode.o CSetROP.o CSetCursor.o CLineRelPath.o CSetColorSpace.o\
	CSetPaintTxMode.o CSetSourceTxMode.o CSetBrushSource.o CSetPenSource.o\
	CSetFillMode.o CRectanglePath.o CBeginFontHeader.o CReadFontHeader.o\
	CBeginChar.o CReadChar.o CSetFont.o CSetCharScale.o CText.o \
	CSetClipRectangle.o CBeginImage.o CReadImage.o CSetClipReplace.o\
	CEndPage.o CSetCharAngle.o CSetLineJoin.o CSetLineCap.o CSetPenWidth.o\
	CSetLineDash.o CRemoveFont.o CBeginStream.o CComment.o CEllipse.o \
	CEllipsePath.o CExecStream.o CReadStream.o CRectangle.o CRemoveStream.o \
	CScanLineRel.o CSetCharAttributes.o CSetCharBoldValue.o CSetCharShear.o \
	CSetCharSubMode.o CSetClipIntersect.o CSetCursorRel.o CSetMiterLimit.o \
	CSetPageRotation.o CTextPath.o CChord.o CChordPath.o CLinePath.o CPie.o \
	CPiePath.o CRoundRectanglePath.o CRoundRectangle.o CArcPath.o \
	CBeginRastPattern.o CReadRastPattern.o CBezierPath.o CBezierRelPath.o \
	CSetHalftoneMethod.o CVendorUnique.o CPjlOperator.o CPclOperator.o \
	ParserFunction.o Parser.o ParserErrno.o
# Parser.o CreateAttribute.o  \CEmbedType.o \

LIBS =

ROOT_INCLUDE = -I ../
BOOST_INCLUDE = -I ../boost

CC = gcc
CXX = g++

CXXFLAGS = -O0 -g3 -Werror -Wall -fmessage-length=0
CFLAGS = -O0 -g3 -Werror -Wall -fmessage-length=0

ANOTHER_CXXFLAGS = $(BOOST_INCLUDE) $(ROOT_INCLUDE)

LDFLAGS = $(LIBS)

all: $(TARGET)

$(TARGET): $(OBJS)
#	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)
	ar r $(TARGET) $(OBJS)

.c.o:
	$(CC) -c $(CFLAGS) $<

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(ANOTHER_CXXFLAGS) $<

.a.o: $(OBJC)
	ar r $<

clean:
	-rm -fv $(OBJS) $(TARGET)

.PHONY: clean $(TARGET)
