#include "button.h"

Button::Button( SDL_Rect destination_rectangle, SDL_Surface* image )//, Object source_object )
: dest_rect_(destination_rectangle), img_(image)
{
	//_source_object = source_object;
}

void Button::update( Position mouse_pos, bool mouse_clicked )
{
	if( mouse_clicked && 
		point_is_inside_button( mouse_pos ) )
		activate_click_event();
}

void Button::draw( SDL_Surface* screen )
{
	SDL_Rect img_rect;
	img_rect.x = 0;
	img_rect.y = 0;
	img_rect.w = img_->w;
	img_rect.h = img_->h;

	SDL_BlitSurface( img_, &img_rect, screen, &dest_rect_);
}

void Button::activate_click_event()
{
	click_event.notify();
}

bool Button::point_is_inside_button( Position point )
{
	return 
		(point.x - dest_rect_.x) < dest_rect_.w &&
		(point.x - dest_rect_.x) > 0 &&
		(point.y - dest_rect_.y) < dest_rect_.h &&
		(point.y - dest_rect_.y) > 0 ;
}