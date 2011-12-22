/*****************************************************************************
 * NasuTek Commander
 * Copyright © 2012 NasuTek Enterprises <mmanley@nasutek.com>
 * Copyright © 2005-2008 Piotr Pszczolkowski <piotr@beesoft.org>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/

/*------- include files:
-------------------------------------------------------------------*/
#include "QBtViewDelegate.h"
#include "QBtViewModel.h"
#include "QBtViewItem.h"
#include "QBtView.h"
#include "QBtConfig.h"
#include <QApplication>
#include <QPalette>
#include <QtDebug>

//*******************************************************************
// QBtViewDelegate                                       CONSTRUCTOR
//*******************************************************************
QBtViewDelegate::QBtViewDelegate( QBtView* const in_view )
: QItemDelegate ( in_view )
, view_         ( in_view )
{}
// end of QBtViewDelegate

//*******************************************************************
// paint                                           PRIVATE inherited
//*******************************************************************
void QBtViewDelegate::paint(  QPainter*                   in_painter,
                              const QStyleOptionViewItem& in_options,
                              const QModelIndex&          in_index ) const
{
   const QBtViewModel* const model = dynamic_cast< QBtViewModel* >( view_->model() );
   const QBtViewItem*  const   hit = model->head_item( in_index );
   QStandardItem* const        cit = model->itemFromIndex( in_index );
   QBtConfig* const            cfg = QBtConfig::instance();
   
   const bool current_row  = ( view_->currentIndex().row() == in_index.row() );
   const bool selected     = ( hit ) ? hit->selected() : false;
   const bool has_focus    = view_->hasFocus();

   QStyleOptionViewItem options = in_options;
   QPalette palette             = options.palette;

      
   if( has_focus ) {
      if( current_row ) {
         if( selected ) {
            palette.setColor( QPalette::Highlight      , cfg->bkg_f_c_s_color() );
            palette.setColor( QPalette::HighlightedText, cfg->txt_f_c_s_color() );
         }
         else {
            palette.setColor( QPalette::Highlight      , cfg->bkg_f_c_ns_color() );
            palette.setColor( QPalette::HighlightedText, cfg->txt_f_c_ns_color() );
         }
      }
      else {
         if( selected ) {
            cit->setBackground( cfg->bkg_f_nc_s_color() );
            cit->setForeground( cfg->txt_f_nc_s_color() );
         }
         else {
            cit->setBackground( cfg->bkg_f_nc_ns_color() );
            cit->setForeground( cfg->txt_f_nc_ns_color() );
         }
      }
   }
   else {
      if( current_row ) {
         if( selected ) {
            palette.setColor( QPalette::Highlight      , cfg->bkg_nf_c_s_color() );
            palette.setColor( QPalette::HighlightedText, cfg->txt_nf_c_s_color() );
         }
         else {
            palette.setColor( QPalette::Highlight      , cfg->bkg_nf_c_ns_color() );
            palette.setColor( QPalette::HighlightedText, cfg->txt_nf_c_ns_color() );
         }
      }
      else {
         if( selected ) {
            cit->setBackground( cfg->bkg_nf_nc_s_color() );
            cit->setForeground( cfg->txt_nf_nc_s_color() );
         }
         else {
            cit->setBackground( cfg->bkg_nf_nc_ns_color() );
            cit->setForeground( cfg->txt_nf_nc_ns_color() );
         }
      }
   }
   options.palette = palette;
   QItemDelegate::paint( in_painter, options, in_index );
}
// end of paint
