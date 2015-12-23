#ifndef INCLUDED_MOVE_
#define INCLUDED_MOVE_

class Move
{
  int d_value;

public:
  Move(int value);
  int getValue() const;
};

inline int Move::getValue() const
{
  return d_value;
} 

#endif
